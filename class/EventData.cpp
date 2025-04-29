/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 20:17:07 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/EventData.hpp"

EventData::EventData(int fd, int type, IEventHandler& ctx) : _fd(fd), 
	_type(type), _ctx(ctx) {}

EventData::EventData(const EventData &obj) : _fd(obj._fd), _type(obj._type),
	_ctx(obj._ctx) {}

EventData::~EventData() {}

EventData &EventData::operator=(const EventData& obj)
{
	if (this != &obj)
		this->_ctx = obj._ctx;
	return (*this);
}

int EventData::getFd() const
{
	return (this->_fd);
}

int EventData::getType() const
{
	return (this->_type);
}

const IEventHandler& EventData::getCtx() const
{
	return (this->_ctx);
}

void EventData::onRead() const
{
	this->_ctx.onReadEvent(this->_fd, this->_type);
}

void EventData::onWrite() const
{
	this->_ctx.onWriteEvent(this->_fd, this->_type);
}

void EventData::onClose() const
{
	this->_ctx.onCloseEvent(this->_fd, this->_type);
}

