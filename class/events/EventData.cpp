/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:09:57 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/events/EventData.hpp"

EventData::EventData(int fd, int type, IEventHandler& ctx, EventMonitoring &em) 
	: _fd(fd), _type(type), _ctx(ctx), _em(em) {}

EventData::EventData(const EventData &obj) : _fd(obj._fd), _type(obj._type),
	_ctx(obj._ctx), _em(obj._em) {}

EventData::~EventData() {}

EventData &EventData::operator=(const EventData& obj)
{
	if (this != &obj)
	{
		this->_ctx = obj._ctx;
		this->_em = obj._em;
	}
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
	this->_ctx.onReadEvent(this->_fd, this->_type, this->_em);
}

void EventData::onWrite() const
{
	this->_ctx.onWriteEvent(this->_fd, this->_type, this->_em);
}

void EventData::onClose() const
{
	this->_ctx.onCloseEvent(this->_fd, this->_type, this->_em);
}

