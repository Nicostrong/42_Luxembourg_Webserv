/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:56:43 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/networking/Socket.hpp"
#include "../../includes/networking/SocketManager.hpp"
#include "../../includes/handling/RequestHandling.hpp"

Socket::Socket(int fd, const Endpoint& sockAddr, const Endpoint& entryAddr, 
	ServerManager& sm, SocketManager& sockm)
	: _fd(fd), _sockAddr(sockAddr), _entryAddr(entryAddr), 
	_rxBuffer(RX_SIZE), _txBuffer(RESPONSE_BUFFER_SIZE), _reset(false), 
	_keepAlive(true), _isDataSent(false), _sm(sm), _sockm(sockm), _em(NULL)
{
	this->_req 		= HttpRequest(this->_sockAddr.getIp().getIpString());
	LOG_INFO("Socket opened on " << this->_sockAddr);
}

Socket::~Socket() 
{
	if (this->_fd > 2)
		close(this->_fd);
	
	if (this->_handler.getCGI() && this->_handler.getCGI()->getPid() != 0)
		LOG_INFO("Socket" << this->_sockAddr << " closed");
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
			throw std::runtime_error("read failed");
			
		this->_rxBuffer.setBufferUsed(bytes);
		this->_handler.onRead(em, this);
	}
	catch(const HttpExceptions& e)
	{
		if (dynamic_cast<const HttpSevereExceptions*>(&e))
			this->_handler.setConnectionClose(*this);
		if (e.getCode() > 399)
			LOG_ERROR("Client/Server HTTP errror " << e.getCode());
		setError((HttpBase::HttpCode)e.getCode(), em);
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		setError(HttpBase::INTERNAL_SERVER_ERROR, em);
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
			LOG_INFO(this->_resp.getStatusCode() << " " << this->_req.getMethod() << " " 
					 << this->_req.getUri() << " " << this->_req.getHttpVersion());
			if (!this->_keepAlive)
				this->_sockm.remove(*this, em);
			else
				reset(em);
		}
	}
	catch(const HttpExceptions& e)
	{
		if (dynamic_cast<const HttpSevereExceptions*>(&e))
			this->_handler.setConnectionClose(*this);
		if (e.getCode() > 399)
			LOG_ERROR("Client/Server HTTP errror " << e.getCode());
		setError((HttpBase::HttpCode)e.getCode(), em);
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		setError(HttpBase::INTERNAL_SERVER_ERROR, em);
	}
}

void Socket::onCloseEvent(int fd, EventMonitoring &em)
{
	LOG_INFO("Socket " << this->_sockAddr << " closed by remote");
	this->_sockm.remove(*this, em);
	(void)fd;
}

void Socket::onTickEvent(int fd, EventMonitoring& em)
{
	try
	{
		this->_handler.onTick(em, this);
	}
	catch(const CGI::CGIExit& e)
	{
		throw EventMonitoring::EPollCatchBypass();
	}
	catch(const HttpExceptions& e)
	{
		if (dynamic_cast<const HttpSevereExceptions*>(&e))
			this->_handler.setConnectionClose(*this);
		if (e.getCode() > 399)
			LOG_ERROR("Client/Server HTTP errror " << e.getCode());
		setError((HttpBase::HttpCode)e.getCode(), em);
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		setError(HttpBase::INTERNAL_SERVER_ERROR, em);
	}
	(void)fd;
}

void	Socket::setEM( EventMonitoring& ev )
{
	this->_em = &ev;
	return ;
}

void Socket::setError(HttpBase::HttpCode code, EventMonitoring& em)
{
	if (!this->_isDataSent)
	{
		this->_txBuffer.reset();
		this->_resp.setRespType(HttpResponse::ERROR);
		this->_resp.setStatusCode(code);
		try
		{
			if (this->_req.getCustomErrorPage() || !this->_req.getServer())
				this->_req.setCustomErrorPage(false);
			else
			{
				struct stat infos;
				std::string path = this->_req.getServer()->getPathError(code);
				this->_req.setCustomErrroPagePath(path);
				this->_req.setCustomErrorPage(true);

				if (stat(path.c_str(), &infos) == -1 || !S_ISREG(infos.st_mode) ||
					access(path.c_str(), R_OK) == -1)
					this->_req.setCustomErrorPage(false);
				else
					this->_resp.addHeader("Content-Length", infos.st_size);
			}
		}
		catch (const std::exception& ex) {}

		this->getHandler().getResponseHandling().init(*this);
		em.monitorUpdate(this->_fd, POLLOUT | EPOLLTICK | POLLHUP | POLLRDHUP);
	}
	else
		this->_sockm.remove(*this, em);
}
