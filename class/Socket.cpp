/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 08:46:28 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Socket.hpp"
#include "../includes/SocketManager.hpp"
#include "../includes/RequestHandling.hpp"

Socket::Socket(int fd, const Endpoint& sockAddr, const Endpoint& entryAddr, 
	ServerManager& sm, SocketManager& sockm)
	: _fd(fd), _sockAddr(sockAddr), _entryAddr(entryAddr), _resp(), 
	  _rxBuffer(RX_SIZE), _txBuffer(RESPONSE_BUFFER_SIZE), _reset(false), 
	  _keepAlive(true), _sm(sm), _sockm(sockm)
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

Buffer& Socket::getTxBuffer()
{
	return (this->_txBuffer);
}

ServerManager& Socket::getSM()
{
	return (this->_sm);
}

void Socket::reset()
{
	this->_reset = true;
}

void Socket::onReadEvent(int fd, int type, EventMonitoring &em)
{
	(void)type;
	try
	{
		try
		{
			if (this->_rxBuffer.isBufferRead())
				this->_rxBuffer.reset();
			
			ssize_t bytes = recv(fd, this->_rxBuffer.getDataUnused(), 
				this->_rxBuffer.getBufferUnused(), 0);
				
			if (bytes == -1)
				throw SocketReadException();
			
			this->_rxBuffer.setBufferUsed(bytes);
			this->_req.onRequest(this->_rxBuffer, *this);
			
			if (this->_req.getState() < HttpParser::HTTP_RECEIVED)
				return ;

			this->_rHandler.init(*this);
			em.unmonitor(fd);
			em.monitor(fd, POLLOUT | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
		}
		catch(const HttpExceptions& e)
		{
			if (dynamic_cast<const HttpSevereExceptions*>(&e))
			{
				this->_keepAlive = false;
				this->_resp.addHeader("Connection", "close");
			}
			LOG_ERROR("An error occured while parsing request "
				"(can be bad request as well)");
			LOG_ERROR(e.getCode());
			
			this->_resp.setRespType(HttpResponse::ERROR);
			this->_resp.setStatusCode((HttpBase::HttpCode)e.getCode());
			this->_rHandler.init(*this);
			em.unmonitor(fd);
			em.monitor(fd, POLLOUT | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
		}
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		this->_sockm.remove(*this, em);
	}
}

void Socket::onWriteEvent(int fd, int type, EventMonitoring &em)
{
	try
	{
		if (this->_txBuffer.isBufferRead())
			this->_txBuffer.reset();
		this->_rHandler.send(*this);
		if (!this->_txBuffer.isBufferRead())
		{
			int dataSent = send(fd, this->_txBuffer.getDataUnread(), 
				this->_txBuffer.getBufferUnread(), 0);
			if (dataSent == -1)
				throw std::runtime_error("send failed");
			this->_txBuffer.setBufferRead(dataSent);
		}
		if (this->_reset && this->_txBuffer.isBufferRead())
		{
			if (!this->_keepAlive)
			{
				this->_sockm.remove(*this, em);
				return ;
			}
			this->_req = HttpRequest(this->_sockAddr.getIp().getIpString());
			this->_resp = HttpResponse();
			this->_txBuffer.reset();
			this->_rHandler.reset();
			em.unmonitor(fd);
			em.monitor(fd, POLLIN | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
			this->_reset = false;
		}
	}
	catch(const std::exception& e)
	{
		this->_sockm.remove(*this, em);
	}
	(void)type;
}

void Socket::onCloseEvent(int fd, int type, EventMonitoring &em)
{
	this->_sockm.remove(*this, em);
	(void)fd;
	(void)em;
	(void)type;
}

// Custom exceptions

const char* Socket::SocketReadException::what() const throw()
{
	return ("Read Exception");
}
