/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_ev.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 15:19:22 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/CGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		CGI::onReadEvent(int fd, EventMonitoring& em)
{
	this->_isReadEvent = true;
	this->_rxBuffer.resetIfRead();

	try
	{
		ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
									this->_rxBuffer.getBufferUnused());

		if (bytes == -1)
			throw CGIError("Error reading pipe from GCI");

		if (bytes == 0)
		{
			onEndOutput(em);
			return ;
		}

		setByteRead(bytes);
		this->_rxBuffer.setBufferUsed(bytes);
		
		LOG_DEB("BUFF:\n" << getRxBuffer());
		
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
	}
	catch(const std::exception& e)
	{
		onCgiError(em);
	}
}

void		CGI::onWriteEvent(int fd, EventMonitoring& em)
{
	try
	{
		Body* 		body = this->_socket->getReq().getBody();
		bool 		eof = false;

		if (body)
		{
			eof = body->read(this->_txBuffer);
			ssize_t bytes = write(fd,
						this->_txBuffer.getDataUnread(), 
						this->_txBuffer.getBufferUnread());

			if (bytes == -1)
				throw CGIError("send data on pipe failed");
			setByteSend(bytes);
			this->_txBuffer.setBufferRead(bytes);
			eof &= this->_txBuffer.isBufferRead();
		}
		
		if (!body || eof)
		{
			onEndInput(em);
			return ;
		}
			
	}
	catch(const std::exception& e)
	{
		onCgiError(em);
	}
}

void		CGI::onCloseEvent(int fd, EventMonitoring& em)
{
	try
	{
		if (this->getPipeFromCGI().getOut() == fd)
			this->_isCloseEvent = true;
		else
		{
			em.unmonitor(this->getPipeToCGI().getIn());
			this->getPipeToCGI().closeIn();
		}
	}
	catch(const std::exception& e)
	{
		onCgiError(em);
	}
}

void		CGI::onTickEvent( int fd, EventMonitoring& em )
{
	(void)fd;
	int status = 0;

	if (!this->_isExited && this->_pid > 0)
	{
		int pState = waitpid(this->_pid, &status, WNOHANG);
		if (pState == -1 || status != 0)
		{
			onCgiError(em);
			return ;
		}
		else if (pState > 0)
			this->_isExited = true;
	}

	if (!this->_isTransferFinished && this->_isCloseEvent && !this->_isReadEvent)
		onEndOutput(em);

	this->_isCloseEvent = false;
	this->_isReadEvent = false;
	return ;
}

void CGI::onCgiError(EventMonitoring& em)
{
	int status = 0;
	
	CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

	em.unmonitor(this->getPipeToCGI().getIn());
	em.unmonitor(this->getPipeFromCGI().getOut());
	cgiResp->setError();
	cgiResp->setErrorCode(HttpBase::BAD_GATEWAY);
	this->getPipeToCGI().closeIn();
	this->getPipeFromCGI().closeOut();
	resetByteSend();
	resetByteRead();
	if (this->_pid > 0 && waitpid(this->_pid, &status, WNOHANG) == 0)
		kill(this->_pid, SIGKILL);
}

void CGI::onEndOutput(EventMonitoring& em)
{
	em.unmonitor(this->getPipeToCGI().getIn());
	em.unmonitor(this->getPipeFromCGI().getOut());	this->getPipeToCGI().closeIn();
	this->getPipeFromCGI().closeOut();
	resetByteSend();
	resetByteRead();
	this->_isTransferFinished = true;
	this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
}

void CGI::onEndInput(EventMonitoring& em)
{
	em.unmonitor(this->getPipeToCGI().getIn());
	this->getPipeToCGI().closeIn();
	this->_socket->getHandler().setState(HttpHandling::CGI_RECEIVING);
	resetByteSend();
}
