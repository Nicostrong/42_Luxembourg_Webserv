/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/25 14:45:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTMONITORING_HPP
# define EVENTMONITORING_HPP

#include "EventHandler.hpp"
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <poll.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>

#define MAX_CONNECTIONS 20
#define MAX_EVENTS 20
#define TIMEOUT_POLL 5000

class EventMonitoring
{
	public:
		class PollFullException : public std::exception {
			public:
				const char * what () const throw();
		};

		class EPollFailedInitException : public std::exception {
			public:
				const char * what () const throw();
		};

		EventMonitoring();
		EventMonitoring(const EventMonitoring &obj);
		~EventMonitoring();
		EventMonitoring &operator=(const EventMonitoring &obj);
		const std::vector<epoll_event> getEvents() const;
		size_t getClientsConnected() const;
		void monitor(int fd, uint32_t events, EventHandler::BaseDataType type);
		void unmonitor(int fd);
		int  update();
	private:
		std::vector<epoll_event> _events;
		std::vector<epoll_event> _openFds;
		size_t 	_clientsConnected;
		int _epollFd;
};

#endif