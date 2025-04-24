/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 10:05:34 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/EventMonitoring.hpp"

EventMonitoring::EventMonitoring() : _fds(0), _fdsData(0), _clientsConnected(0)
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
		this->_fds = obj._fds;
		this->_fdsData = obj._fdsData;
		this->_clientsConnected = obj._clientsConnected;
		close(this->_epollFd);
		this->_epollFd = obj._epollFd;
	}
	return (*this);
}

const std::vector<pollfd> &EventMonitoring::getFds() const
{
	return (this->_fds);
}

std::vector<BaseData *> &EventMonitoring::getFdsData()
{
	return (this->_fdsData);
}

size_t EventMonitoring::getClientsConnected() const
{
	return (this->_clientsConnected);
}

void EventMonitoring::monitor(int fd, uint32_t events,
							 BaseData::BaseDataType type)
{
	struct epoll_event event;

	if (this->_clientsConnected + 1 == MAX_CONNECTIONS)
		throw PollFullException();

	BaseData *data = BaseData::getHerited(type);

	event.events = events;
	event.data.fd = fd;
	event.data.ptr = data;

	this->_events.push_back(event);
	if (type == BaseData::CLIENT)
		this->_clientsConnected++;
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, fd, &event);
}

void EventMonitoring::unmonitor(int fd)
{
	std::vector<pollfd>::iterator it = this->_fds.begin();
	std::vector<BaseData *>::iterator itFdsData = this->_fdsData.begin();

	while (it != this->_fds.end() && itFdsData != this->_fdsData.end())
	{
		if (it->fd == fd)
		{
			if ((*itFdsData)->getType() == BaseData::CLIENT)
				this->_clientsConnected--;
			delete *itFdsData;
			itFdsData = this->_fdsData.erase(itFdsData);
			it = this->_fds.erase(it);
		}
		else
		{
			++it;
			++itFdsData;
		}
	}
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
}

int EventMonitoring::updatePoll()
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
