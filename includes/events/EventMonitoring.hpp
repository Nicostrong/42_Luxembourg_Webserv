/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMonitoring.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:28:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTMONITORING_HPP
# define EVENTMONITORING_HPP

# include "./../lib.hpp"
# include "./EventData.hpp"
# include "./../utils/Fd.hpp"
# include "./IEventHandler.hpp"

# define MAX_CONNECTIONS 4096
# define MAX_EVENTS 4096
# define TIMEOUT_POLL 5000

class	EventMonitoring
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

		class	EPollCatchBypass: public std::exception
		{
			private:
				std::string		_msg;
			public:
				EPollCatchBypass() throw();
				virtual ~EPollCatchBypass( void ) throw();
				const char*		what() const throw();
		};

		EventMonitoring();
		~EventMonitoring();
		const std::vector<epoll_event> getEvents() const;
		size_t getClientsConnected() const;
		
		void monitor(int fd, uint32_t events, IEventHandler& ctx);
		void monitorUpdate(int fd, uint32_t events);
		void unmonitor(int fd);
		void updateEvents();

	private:

		EventMonitoring(const EventMonitoring &obj);
		EventMonitoring& operator=(const EventMonitoring& obj);

		void 						remove();
		std::vector<epoll_event>	_events;
		std::list<epoll_event>		_openFds;
		size_t 						_clientsConnected;
		int 						_epollFd;
		
};

#endif