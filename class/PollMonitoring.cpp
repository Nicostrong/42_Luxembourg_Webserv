/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollMonitoring.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 18:16:02 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PollMonitoring.hpp"

PollMonitoring::PollMonitoring() : _fds(0) {}

PollMonitoring::PollMonitoring(const PollMonitoring &obj) 
	: _fds(0)
{
	*this = obj;
}

PollMonitoring::~PollMonitoring() {}

PollMonitoring &PollMonitoring::operator=(const PollMonitoring &obj)
{
	if (this != &obj)
		this->_fds = obj._fds;
	return (*this);
}

const std::vector<pollfd> &PollMonitoring::getFds() const
{
	return (this->_fds);
}

std::vector<BaseData*> &PollMonitoring::getFdsData() 
{
	return (this->_fdsData);
}

void PollMonitoring::monitor(int fd, short int events, 
	BaseData::BaseDataType type)
{
	struct pollfd npollfd;
	
	if (_fds.size() == MAX_CONNECTIONS)
		throw PollFullException();

	BaseData *data = BaseData::getHerited(type);

	npollfd.fd = fd;
	npollfd.events = events;
	
	this->_fds.push_back(npollfd);
	this->_fdsData.push_back(data);
}

void PollMonitoring::unmonitor(int fd)
{
	std::vector<pollfd>::iterator it = this->_fds.begin();
	std::vector<BaseData*>::iterator itFdsData = this->_fdsData.begin();
	
    while (it != this->_fds.end() && itFdsData != this->_fdsData.end()) 
	{
        if (it->fd == fd)
		{
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
}

int PollMonitoring::updatePoll()
{
	return (poll(this->_fds.data(), this->_fds.size(), TIMEOUT_POLL));
}

//Exceptions

const char *PollMonitoring::PollFullException::what()
{
	return ("Poll full exception");
}
