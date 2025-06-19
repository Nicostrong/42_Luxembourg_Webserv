/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:51:25 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/events/EventData.hpp"

EventData::EventData(int fd, IEventHandler& ctx, EventMonitoring &em) 
	: _fd(fd), _ctx(ctx), _em(em), _canceled(false) {}

EventData::EventData(const EventData &obj) : _fd(obj._fd), _ctx(obj._ctx), 
	_em(obj._em), _canceled(obj._canceled) {}

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

const IEventHandler& EventData::getCtx() const
{
	return (this->_ctx);
}

bool EventData::getCanceled() const
{
	return (this->_canceled);
}

void EventData::setCanceled()
{
	this->_canceled = true;
}

void EventData::onRead() const
{
	this->_ctx.onReadEvent(this->_fd, this->_em);
}

void EventData::onWrite() const
{
	this->_ctx.onWriteEvent(this->_fd, this->_em);
}

void EventData::onClose() const
{
	this->_ctx.onCloseEvent(this->_fd, this->_em);
}

void EventData::onTick() const
{
	this->_ctx.onTickEvent(this->_fd, this->_em);
}
