/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 10:48:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Socket.hpp"
#include "../includes/server/Server.hpp"
#include "../includes/RequestHandling.hpp"

Socket::Socket(int fd, EventMonitoring&	em, Server& ctx, 
	const sockaddr_in& sockAddr) : _fd(fd),
	_resp(), _em(em), _ctx(ctx), _rxBuffer(RX_SIZE), 
	_txBuffer(RESPONSE_BUFFER_SIZE), _reset(false), _keepAlive(true)
	{
		this->_remoteIp = getReadableIp(sockAddr);
		this->_req 		= HttpRequest(this->_remoteIp);
		LOG_DEB(this->_remoteIp + " opened connection");
	}

Socket::Socket(const Socket& obj) : _fd(obj._fd), _req(obj._req), 
	_resp(obj._resp), _em(obj._em), _ctx(obj._ctx), _remoteIp(obj._remoteIp),
	_rxBuffer(obj._rxBuffer), _txBuffer(obj._txBuffer), _reset(obj._reset), 
	_keepAlive(true), _rHandler(obj._rHandler) {}

Socket::~Socket() {}

Socket& Socket::operator=(const Socket& obj)
{
	if (this != &obj)
	{
		this->_req = obj._req;
		this->_resp = obj._resp;
		this->_rxBuffer = obj._rxBuffer;
		this->_txBuffer = obj._txBuffer;
	}
	return (*this);
}

bool Socket::operator==(const Socket& obj)
{
	return(this->_fd == obj._fd);
}

int Socket::getSocket() const
{
	return (this->_fd);
}

HttpRequest& Socket::getReq()
{
	return (this->_req);
}

HttpResponse& Socket::getResp()
{
	return (this->_resp);
}

Server& Socket::getCtx()
{
	return (this->_ctx);
}

Buffer& Socket::getTxBuffer()
{
	return (this->_txBuffer);
}

EventMonitoring& Socket::getEventMonitoring()
{
	return (this->_em);
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
			//this->_ctx.onSocketClosedEvent(*this);
			em.monitor(fd, POLLOUT | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
		}
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		this->_ctx.onSocketClosedEvent(*this);
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
				this->_ctx.onSocketClosedEvent(*this);
				return ;
			}
			this->_req = HttpRequest(this->_remoteIp);
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
		this->_ctx.onSocketClosedEvent(*this);
	}
	(void)type;
}

void Socket::onCloseEvent(int fd, int type, EventMonitoring &em)
{
	this->_ctx.onSocketClosedEvent(*this);
	(void)fd;
	(void)em;
	(void)type;
}

std::string Socket::getReadableIp(const struct sockaddr_in& addr)
{
	std::stringstream ss;
    uint32_t ip = ntohl(addr.sin_addr.s_addr);
	
    int a = (ip >> 24) & 0xFF;
    int b = (ip >> 16) & 0xFF;
    int c = (ip >> 8) & 0xFF;
    int d = ip & 0xFF;
    
    ss << a << "." << b << "." << c << "." << d;
    return (ss.str());
}

// Custom exceptions

const char* Socket::SocketReadException::what() const throw()
{
	return ("Read Exception");
}
