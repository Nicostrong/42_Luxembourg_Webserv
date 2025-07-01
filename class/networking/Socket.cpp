/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/01 09:43:26 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/networking/Socket.hpp"
#include "./../../includes/networking/SocketManager.hpp"
#include "./../../includes/handling/RequestHandling.hpp"

Socket::Socket(int fd, const Endpoint& sockAddr, const Endpoint& entryAddr, 
	ServerManager& sm, SocketManager& sockm)
	: _fd(fd), _sockAddr(sockAddr), _entryAddr(entryAddr), 
	  _rxBuffer(RX_SIZE), _txBuffer(RESPONSE_BUFFER_SIZE), _reset(false), 
	  _keepAlive(true), _isDataSent(false), _sm(sm), _sockm(sockm), _em(NULL)
{
	this->_req 		= HttpRequest(this->_sockAddr.getIp().getIpString());
	LOG_DEB(this->_sockAddr.getIp().getIpString() + " opened connection");
}

Socket::~Socket() 
{
	if (this->_fd > 2)
		close(this->_fd);
	LOG_DEB(this->_sockAddr.getIp().getIpString() + " closed connection");
}

bool Socket::operator==(const Socket& obj)
{
	return(this->_fd == obj._fd);
}

int Socket::getSocket() const
{
	return (this->_fd);
}

const Endpoint& Socket::getSockAddr() const
{
	return (this->_sockAddr);
}
		
const Endpoint& Socket::getEntryAddr() const
{
	return (this->_entryAddr);
}

HttpRequest& Socket::getReq()
{
	return (this->_req);
}

HttpResponse& Socket::getResp()
{
	return (this->_resp);
}

Buffer& Socket::getRxBuffer()
{
	return (this->_rxBuffer);
}

Buffer& Socket::getTxBuffer()
{
	return (this->_txBuffer);
}

ServerManager& Socket::getSM()
{
	return (this->_sm);
}

SocketManager& Socket::getSockM()
{
	return (this->_sockm);
}

EventMonitoring& Socket::getEM( void )
{
	return (*_em);
}

HttpHandling& Socket::getHandler()
{
	return (this->_handler);
}

bool Socket::getDataSent() const
{
	return (this->_isDataSent);
}

void Socket::setSocketClose()
{
	this->_keepAlive = false;
}

void Socket::setReset()
{
	this->_reset = true;
}

void Socket::reset(EventMonitoring& em)
{
	this->_req = HttpRequest(this->_sockAddr.getIp().getIpString());
	this->_resp = HttpResponse();
	this->_txBuffer.reset();
	this->_handler.reset();
	em.monitorUpdate(this->_fd, POLLIN | EPOLLTICK | POLLHUP | POLLRDHUP);
	this->_reset = false;
	this->_isDataSent = false;
}

void Socket::onReadEvent(int fd, EventMonitoring &em)
{
	try
	{
		this->_rxBuffer.resetIfRead();
			
		ssize_t bytes = recv(fd, this->_rxBuffer.getDataUnused(), 
			this->_rxBuffer.getBufferUnused(), 0);
	
		if (bytes == -1)
			throw SocketReadException();
			
		this->_rxBuffer.setBufferUsed(bytes);
		this->_handler.onRead(em, this);
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		this->_sockm.remove(*this, em);
	}
}

void Socket::onWriteEvent(int fd, EventMonitoring &em)
{
	try
	{
		this->_txBuffer.resetIfRead();

		this->_handler.onWrite(em, this);

		if (!this->_txBuffer.isBufferRead())
		{
			int dataSent = send(fd, this->_txBuffer.getDataUnread(), 
				this->_txBuffer.getBufferUnread(), 0);

			if (dataSent == -1)
				throw std::runtime_error("send failed");

			if (dataSent > 0)
				this->_isDataSent = true;
			
			this->_txBuffer.setBufferRead(dataSent);
		}
		
		if (this->_reset && this->_txBuffer.isBufferRead())
		{
			if (!this->_keepAlive)
				this->_sockm.remove(*this, em);
			else
				reset(em);
		}
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		this->_sockm.remove(*this, em);
	}
}

void Socket::onCloseEvent(int fd, EventMonitoring &em)
{
	LOG_DEB("Connection closed by remote");
	this->_sockm.remove(*this, em);
	(void)fd;
	(void)em;
}

void Socket::onTickEvent(int fd, EventMonitoring& em)
{
	this->_handler.onTick(em, this);
	(void)fd;
	(void)em;
}

void	Socket::setEM( EventMonitoring& ev )
{
	this->_em = &ev;
	return ;
}

// Custom exceptions

const char* Socket::SocketReadException::what() const throw()
{
	return ("Read Exception");
}
