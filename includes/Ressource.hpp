/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:45:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/30 18:02:50 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESSOURCE_HPP
# define RESSOURCE_HPP

#include <iostream>
#include "IEventHandler.hpp"

class Ressource : public IEventHandler
{
	public:
		enum State
		{
			WAITING = 0,
			RECEIVED = 1,
		};
		
		Ressource(int fd);
		Ressource(const Ressource& obj);
		~Ressource();
		Ressource&			operator=(const Ressource& obj);
		State 				getState() const;
		const std::string&	getRaw() const;
		
		void 				onReadEvent(int fd, int type);
		void				onWriteEvent(int fd, int type);
		void				onCloseEvent(int fd, int type);
	private:
		int 		_fd;
		State 		_state;
		std::string	_raw;
};

#endif