/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/30 15:43:13 by nfordoxc         ###   Luxembourg.lu     */
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
	LOG_DEB("Read event");

	try
	{
		if (getEndWrite())
		{
			this->_rxBuffer.resetIfRead();
			ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
										this->_rxBuffer.getBufferUnused());

			setByteRead(bytes);

			std::cout << "DEBUG CGI on READ" << std::endl;
			std::cout << "nb bytes lu: " << bytes << std::endl;
			std::cout << "size du buff " << getRxBuffer().getBufferSize() << std::endl;
			std::cout << "nb bytes dans le buff " << getRxBuffer().getBufferUnread() << std::endl;
			LOG_DEB("BUFF:\n" << getRxBuffer().getDataUnread());
			std::cout << "TOTAL READ: " << getByteRead() << std::endl;
			
			if (bytes == -1)
				throw CGIError("Error reading pipe from GCI");

			if (bytes == 0)
			{
				LOG_DEB("BUFF: " << getRxBuffer().getBufferUnread());
				this->setIsFinish();
				this->_socket->getHandler().getCgiResponse().setEofReceived();
				this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
				em.unmonitor(fd);
				this->getPipeFromCGI().closeOut();
				resetByteRead();

				return ;
			}

			this->_rxBuffer.setBufferUsed(bytes);
			this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
			
			LOG_DEB("EOF " << (getByteRead() == getRxBuffer().getBufferUnread() ? "YES" : "NOOOO"));
			LOG_DEB("buff unread: " << getRxBuffer().getBufferUnread());
		}
	}
	catch(const std::exception& e)
	{
		CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

		this->setIsFinish();
		em.unmonitor(fd);
		cgiResp->setError();
		cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
		resetByteRead();
		this->getPipeFromCGI().closeOut();
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	try
	{
		if (!this->getEndWrite())
		{
			ssize_t		dataSent;
			Body* 		body = this->_socket->getReq().getBody();
			bool 		eof = false;

			if (body)
			{
				body->read(this->_txBuffer);
				dataSent = write(fd,
							this->_txBuffer.getDataUnread(), 
							this->_txBuffer.getBufferUnread());

				setByteSend(dataSent);
				eof = (body->getSize() == getByteSend());
				if (dataSent == -1)
					throw CGIError("send data on pipe failed");
				this->_txBuffer.setBufferRead(dataSent);
			}
			
			if (!body || (eof && this->_txBuffer.isBufferRead()))
			{
				this->setEndWrite();
				em.unmonitor(fd);
				this->getPipeToCGI().closeIn();
				resetByteSend();
				this->_socket->getHandler().setState(HttpHandling::CGI_RECEIVING);
				return ;
			}
			
		}
	}
	catch(const std::exception& e)
	{
		CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

		em.unmonitor(fd);
		cgiResp->setError();
		cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
		this->getPipeToCGI().closeIn();
		resetByteSend();
		std::cerr << e.what() << std::endl;
		throw e;
	}
	return ;
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	if (this->getPipeFromCGI().getOut() == fd)
		this->_isCloseEvent = true;
	(void)em;
	(void)fd;
	/*LOG_DEB("CLOSE");
	(void)fd;
	(void)em;
	if (this->getPipeFromCGI().getOut() == fd)
	{
		this->_socket->getHandler().getCgiResponse().setEofReceived();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		em.unmonitor(fd);
		this->getPipeFromCGI().closeOut();
		this->setIsFinish();
	}*/
	
	return ;
}

void		MyCGI::onTickEvent( int fd, EventMonitoring& em )
{
	int		status;

	(void)fd;
	(void)em;
	if (waitpid(this->getPid(), &status, WNOHANG))
		this->setIsFinish();

	// Check if data completely received

	if (this->_isCloseEvent && !this->_isReadEvent)
	{
		this->_socket->getHandler().getCgiResponse().setEofReceived();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		em.unmonitor(fd);
		this->getPipeFromCGI().closeOut();
		this->setIsFinish();
		return ;
	}

	this->_isCloseEvent = false;
	this->_isReadEvent = false;
	return ;
}