/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 09:01:39 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Socket.hpp"
#include "../includes/Server.hpp"
#include "../includes/RequestHandling.hpp"

Socket::Socket(int fd, EventMonitoring&	em, Server& ctx, 
	const sockaddr_in& sockAddr) : _fd(fd), _resp(), _em(em), _ctx(ctx) 
	{
		this->_remoteIp = getReadableIp(sockAddr);
		this->_req 		= HttpRequest(this->_remoteIp);
		LOG_DEB(this->_remoteIp + " opened connection");
	}

Socket::Socket(const Socket& obj) : _fd(obj._fd), _req(obj._req), 
	_resp(obj._resp), _em(obj._em), _ctx(obj._ctx), _remoteIp(obj._remoteIp) {}

Socket::~Socket() {}

Socket& Socket::operator=(const Socket& obj)
{
	if (this != &obj)
	{
		this->_req = obj._req;
		this->_resp = obj._resp;
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

void Socket::onReadEvent(int fd, int type, EventMonitoring &em)
{
	(void)type;
	(void)em;
	_req.readReceived(fd);
	if (_req.isReceived())
	{
		em.unmonitor(fd);
		em.monitor(fd, POLLOUT | POLLHUP | POLLRDHUP,
			EventData::CLIENT, *this);
		RequestHandling::getResponse(this->_ctx, this->_req, this->_resp);
	}
}

void Socket::onWriteEvent(int fd, int type, EventMonitoring &em)
{
	(void)type;
	(void)fd;
	(void)em;
	this->_resp.encodeResponse();
	if (this->_resp.isEncoded())
	{
		send(fd, this->_resp.getRaw().c_str(), this->_resp.getRaw().size(), 0);
		this->_req = HttpRequest(this->_remoteIp);
		this->_resp = HttpResponse();
		//this->_ctx.onSocketClosedEvent(*this);
		em.unmonitor(fd);
		em.monitor(fd, POLLIN | POLLHUP | POLLRDHUP,
			EventData::CLIENT, *this);
	}
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