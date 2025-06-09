/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/09 20:41:21 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTMONITORING_HPP
# define EVENTMONITORING_HPP

#include "./../lib.hpp"
#include "./EventData.hpp"
#include "./IEventHandler.hpp"

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

		class EPollFailedWaitException : public std::exception {
			public:
				const char * what () const throw();
		};

		EventMonitoring();
		EventMonitoring(const EventMonitoring &obj);
		~EventMonitoring();
		EventMonitoring& operator=(const EventMonitoring& obj);
		const std::vector<epoll_event> getEvents() const;
		size_t getClientsConnected() const;
		
		void monitor(int fd, uint32_t events, int type, IEventHandler& ctx);
		void monitorUpdate(int fd, uint32_t events);
		void unmonitor(int fd);
		void updateEvents();
	private:
		void 						remove();
		std::vector<epoll_event>	_events;
		std::list<epoll_event>		_openFds;
		std::list<int>				_closeFds;
		size_t 						_clientsConnected;
		int 						_epollFd;
};

#endif