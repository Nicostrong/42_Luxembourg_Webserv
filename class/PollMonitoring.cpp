/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollMonitoring.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 15:41:48 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PollMonitoring.hpp"

PollMonitoring::PollMonitoring() : _fds(0) {}

PollMonitoring::PollMonitoring(const PollMonitoring &obj) 
	: _fds(MAX_CONNECTIONS)
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

void PollMonitoring::monitor(int fd, short int events)
{
	struct pollfd npollfd;

	npollfd.fd = fd;
	npollfd.events = events;
	if (_fds.size() == MAX_CONNECTIONS)
		throw PollFullException();
	this->_fds.push_back(npollfd);
}

void PollMonitoring::unmonitor(int fd)
{
	std::vector<struct pollfd>::iterator it = this->_fds.begin();
    
    while (it != this->_fds.end()) {
        if (it->fd == fd)
            it = this->_fds.erase(it);
        else 
            ++it;
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
