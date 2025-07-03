/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/03 15:45:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		MyCGI::onReadEvent(int fd, EventMonitoring& em)
{
	this->_isReadEvent = true;
	this->_rxBuffer.resetIfRead();

	try
	{
		ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
									this->_rxBuffer.getBufferUnused());

		//std::cout << "DEBUG CGI on READ" << std::endl;
		//std::cout << "nb bytes lu: " << bytes << std::endl;
		//std::cout << "size du buff " << getRxBuffer().getBufferSize() << std::endl;
		
		//std::cout << "TOTAL READ: " << getByteRead() << std::endl;
		
		if (bytes == -1)
			throw CGIError("Error reading pipe from GCI");

		if (bytes == 0)
		{
			onEndOutput(fd, em);
			return ;
		}

		setByteRead(bytes);
		//LOG_DEB("BUFF:\n" << getRxBuffer().getDataUnread());
		

		this->_rxBuffer.setBufferUsed(bytes);
		//std::cout << getRxBuffer();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
	}
	catch(const std::exception& e)
	{
		onCgiError(fd, em);
	}
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
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
			onEndInput(fd, em);
			return ;
		}
			
	}
	catch(const std::exception& e)
	{
		onCgiError(fd, em);
	}
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
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
		onCgiError(fd, em);
	}
}

void		MyCGI::onTickEvent( int fd, EventMonitoring& em )
{
	if (this->_isCloseEvent && !this->_isReadEvent)
	{
		onEndOutput(fd, em);
		return ;
	}

	this->_isCloseEvent = false;
	this->_isReadEvent = false;
	return ;
}

void MyCGI::onCgiError(int fd, EventMonitoring& em)
{
	(void)fd;
	CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

	em.unmonitor(this->getPipeToCGI().getIn());
	em.unmonitor(this->getPipeFromCGI().getOut());
	cgiResp->setError();
	cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
	this->getPipeToCGI().closeIn();
	this->getPipeFromCGI().closeOut();
	resetByteSend();
	resetByteRead();
}

void MyCGI::onEndOutput(int fd, EventMonitoring& em)
{
	(void)fd;
	CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

	em.unmonitor(this->getPipeToCGI().getIn());
	em.unmonitor(this->getPipeFromCGI().getOut());
	cgiResp->setEofReceived();
	this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
	this->getPipeToCGI().closeIn();
	this->getPipeFromCGI().closeOut();
	resetByteSend();
	resetByteRead();
}

void MyCGI::onEndInput(int fd, EventMonitoring& em)
{
	(void)fd;

	em.unmonitor(this->getPipeToCGI().getIn());
	this->getPipeToCGI().closeIn();
	this->_socket->getHandler().setState(HttpHandling::CGI_RECEIVING);
	resetByteSend();
}
