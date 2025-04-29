/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/29 10:02:47 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/EventMonitoring.hpp"

EventMonitoring::EventMonitoring() :  _events(MAX_EVENTS), _openFds(0), 
	_clientsConnected(0)
{
	this->_epollFd = epoll_create1(0);
	if (this->_epollFd == -1)
		throw EPollFailedInitException();
}

EventMonitoring::EventMonitoring(const EventMonitoring &obj)
{
	*this = obj;
}

EventMonitoring::~EventMonitoring() 
{
	std::list<epoll_event>::const_iterator it = this->_openFds.begin();
	while (it != _openFds.end())
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (data->getFd() > 2)
			close(data->getFd());
		delete data;
	}
	this->_openFds.clear();
	if (this->_epollFd > 2)
		close(this->_epollFd);
}

EventMonitoring &EventMonitoring::operator=(const EventMonitoring &obj)
{
	(void)obj;
	return (*this);
}

const std::vector<epoll_event> EventMonitoring::getEvents() const
{
	return (this->_events);
}

size_t EventMonitoring::getClientsConnected() const
{
	return (this->_clientsConnected);
}

void EventMonitoring::monitor(int fd, uint32_t events, int type, 
	IEventHandler& ctx)
{
	epoll_event event;

	if (this->_clientsConnected + 1 == MAX_CONNECTIONS)
		throw PollFullException();

	event.events = events;
	event.data.ptr = new EventData(fd, type, ctx);
	this->_openFds.push_front(event);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, fd, &event);
}

void EventMonitoring::unmonitor(int fd)
{
	std::list<epoll_event>::iterator it = this->_openFds.begin();

	while (it != this->_openFds.end())
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (data->getFd() == fd)
		{
			delete data;
			it = this->_openFds.erase(it);
		}
		else
			++it;
	}
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
}

void EventMonitoring::updateEvents()
{
	int res = epoll_wait(this->_epollFd, this->_events.data(), MAX_EVENTS, -1);
	if (res == -1)
		throw EPollFailedWaitException(); 
	std::vector<epoll_event>::const_iterator it = this->_events.begin();
	while (it != this->_events.begin() + res)
	{
		EventData *data = static_cast<EventData *>(it->data.ptr);
		if (it->events & (POLLERR | POLLHUP | POLLRDHUP))
			data->onClose();
		else if (it->events & POLLIN)
			data->onRead();
		else if (it->events & POLLOUT)
			data->onWrite();
		it++;
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
