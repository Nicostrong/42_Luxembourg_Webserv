/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 10:02:34 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Socket.hpp"
#include "../includes/Server.hpp"

Socket::Socket(int fd, EventMonitoring&	em, Server& ctx) : _fd(fd), _req(), 
	_resp(), _em(em), _ctx(ctx) {}

Socket::Socket(const Socket& obj) : _fd(obj._fd), _req(obj._req), 
	_resp(obj._resp), _em(obj._em), _ctx(obj._ctx) {}

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
	
}

void Socket::onWriteEvent(int fd, int type, EventMonitoring &em)
{
	(void)type;
	(void)fd;
	(void)em;
	//_resp.encodeResponse(_req);
}

void Socket::onCloseEvent(int fd, int type, EventMonitoring &em)
{
	this->_ctx.onSocketClosedEvent(*this);
	(void)fd;
	(void)em;
	(void)type;
}