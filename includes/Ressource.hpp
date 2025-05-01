/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:45:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 10:17:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESSOURCE_HPP
# define RESSOURCE_HPP

#include "lib.hpp"
#include "IEventHandler.hpp"
#include "EventMonitoring.hpp"

#define RESSOURCE_BUFFER_SIZE 1024

class Ressource : public IEventHandler
{
	public:
		enum State
		{
			WAITING = 0,
			RECEIVED = 1,
			ERROR = 2,
		};
		
		Ressource(const std::string& loc, EventMonitoring& em);
		Ressource(const Ressource& obj);
		~Ressource();
		Ressource&			operator=(const Ressource& obj);
		State 				getState() const;
		const std::string&	getRaw() const;
		
		void 				onReadEvent(int fd, int type, EventMonitoring& em);
		void				onWriteEvent(int fd, int type, EventMonitoring& em);
		void				onCloseEvent(int fd, int type, EventMonitoring& em);
	private:
		const std::string&	_loc;
		EventMonitoring&	_em;
		int 				_fd;
		State 				_state;
		std::string			_raw;
};

#endif