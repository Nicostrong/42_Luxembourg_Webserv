/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 14:41:53 by fdehan           ###   ########.fr       */
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
	close(this->_epollFd);
}

EventMonitoring &EventMonitoring::operator=(const EventMonitoring &obj)
{
	if (this != &obj)
	{
		this->_events = obj._events;
		this->_openFds = obj._openFds;
		this->_clientsConnected = obj._clientsConnected;
		close(this->_epollFd);
		this->_epollFd = obj._epollFd;
	}
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

template <typename T>
void EventMonitoring::monitor(int fd, uint32_t events, 
	typename EventHandler<T>::EventsHooks hooks)
{
	epoll_event event;

	if (this->_clientsConnected + 1 == MAX_CONNECTIONS)
		throw PollFullException();

	event.events = events;
	event.data.ptr = new EventHandler(fd, hooks);
	this->_openFds.push_back(event);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, fd, &event);
}

template <typename T>
void EventMonitoring::unmonitor(int fd)
{
	std::vector<epoll_event>::iterator it = this->_openFds.begin();

	while (it != this->_openFds.end())
	{
		EventHandler<T> *data = static_cast<EventHandler<T> *>(it->data.ptr);
		if (data->getFd() == fd)
		{
			
			if (data->getType() == EventHandler::CLIENT)
				this->_clientsConnected--;
			delete data;
			it = this->_openFds.erase(it);
		}
		else
		{
			++it;
		}
	}
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
}

int EventMonitoring::update()
{
	return (epoll_wait(this->_epollFd, this->_events.data(), MAX_EVENTS, -1));
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
