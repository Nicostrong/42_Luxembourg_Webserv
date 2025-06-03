/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:30:40 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/02 13:00:51 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
#define HandleCGI_HPP

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include "../../includes/Pipe.hpp"

class HandleCGI: public IEventHandler
{
	public:
		HandleCGI();
		HandleCGI(HandleCGI& copy);
		HandleCGI& operator=(HandleCGI& copy);
		~HandleCGI();
		void UpdateNewsLetter(const char *compiler, const char *script);
		void UpdateShowData(const char *compiler, const char *script);
		std::string DoCGI(const char *cmd_list[3],EventMonitoring& em);
		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
};

#endif