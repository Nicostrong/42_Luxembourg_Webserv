/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:24:41 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/events/EventMonitoring.hpp"

EventMonitoring::EventMonitoring() :  _events(4096),
	_clientsConnected(0)
{
	this->_epollFd = epoll_create(MAX_EVENTS);
	if (this->_epollFd == -1)
		throw EPollFailedInitException();
	Fd::setNoInheritance(this->_epollFd);
}

EventMonitoring::~EventMonitoring() 
{	
	std::list<epoll_event>::const_iterator it = this->_openFds.begin();
	while (it != _openFds.end())
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		delete data;
		++it;
	}
	this->_openFds.clear();
	if (this->_epollFd > 2)
		close(this->_epollFd);
}

const std::vector<epoll_event> EventMonitoring::getEvents() const
{
	return (this->_events);
}

size_t EventMonitoring::getClientsConnected() const
{
	return (this->_clientsConnected);
}

void EventMonitoring::monitor(int fd, uint32_t events, 
	IEventHandler& ctx)
{
	epoll_event event;

	if (this->_clientsConnected >= this->_events.size())
		this->_events.resize(this->_events.size() * 2);

	event.events = events;
	event.data.ptr = new EventData(fd, ctx, *this);
	this->_openFds.push_back(event);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, fd, &event);
}

void EventMonitoring::monitorUpdate(int fd, uint32_t events)
{
	std::list<epoll_event>::iterator it = this->_openFds.begin();
    while (it != this->_openFds.end())
    {
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (data->getFd() == fd)
        {
			it->events = events;
			epoll_ctl(this->_epollFd, EPOLL_CTL_MOD, fd, &(*it));
			return ;
		}
		++it;
	}
}

void EventMonitoring::unmonitor(int fd)
{
	if (fd <= 2)
		return ;
	
	std::list<epoll_event>::iterator it = this->_openFds.begin();
	
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
	while (it != this->_openFds.end())
    {
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (data->getFd() == fd)
		{
			data->setCanceled();
			return ;
		}
		++it;
	}
}

void EventMonitoring::updateEvents()
{
	int res = epoll_wait(this->_epollFd, this->_events.data(), MAX_EVENTS, 500);
	if (res == -1)
	{
		if (errno == EINTR)
			return ;
		throw EPollFailedWaitException();
	}
	
	std::vector<epoll_event>::const_iterator it = this->_events.begin();
	while (it != this->_events.begin() + res)
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		try
		{
			if (it->events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP) && 
				!data->getCanceled())
			{
				//LOG_DEB("Close epoll event");
				data->onClose();
			}
			if (it->events & EPOLLIN && !data->getCanceled())
			{
				//LOG_DEB("Read epoll event");
				data->onRead();
			}
			if (it->events & EPOLLOUT && !data->getCanceled())
			{
				//LOG_DEB("Write epoll event");
				data->onWrite();
			}
		}
		catch(const EPollCatchBypass& e) 
		{
			throw e;
		}
		catch(const std::exception& e) {}
		it++;
	}
	
	std::list<epoll_event>::const_iterator itTick;
	for (itTick = this->_openFds.begin(); itTick != this->_openFds.end(); ++itTick)
	{
		EventData *data = static_cast<EventData *>(itTick->data.ptr);
		try
		{
			if (itTick->events & EPOLLTICK && !data->getCanceled())
				data->onTick();
		}
		catch(const EPollCatchBypass& e) 
		{
			throw e;
		}
		catch(const std::exception& e) {}
	}
	remove();
}

void EventMonitoring::remove()
{
	std::list<epoll_event>::iterator it = this->_openFds.begin();

	while (it != this->_openFds.end())
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (data->getCanceled())
		{
			delete data;
			it = this->_openFds.erase(it);
			continue;
		}
		++it;
	}
}

// Exceptions

const char *EventMonitoring::PollFullException::what() const throw()
{
	return ("Poll full exception");
}

const char *EventMonitoring::EPollFailedInitException::what() const throw()
{
	return ("EPoll failed initialization exception");
}

const char *EventMonitoring::EPollFailedWaitException::what() const throw()
{
	return ("EPoll failed wait exception");
}

EventMonitoring::EPollCatchBypass::EPollCatchBypass() throw() : _msg("Epoll catch bypass") {}

EventMonitoring::EPollCatchBypass::~EPollCatchBypass( void ) throw() {}

const char*		EventMonitoring::EPollCatchBypass::what() const throw()
{
	return (this->_msg.c_str());
}