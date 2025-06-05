/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:30:40 by gzenner           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/05 10:08:34 by gzenner          ###   ########.fr       */
=======
/*   Updated: 2025/06/05 09:55:47 by fdehan           ###   ########.fr       */
>>>>>>> 57ecd7f1a96ced8d81fbf58b3791aecd59b5d6a7
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
#define HandleCGI_HPP

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include "../../includes/Pipe.hpp"
#include "../../includes/BodyParsing.hpp"

class HandleCGI: public IEventHandler
{
	private:
		BodyParser *bp;
		std::vector<char> receivedTxtBuffer;
		std::string output;
		std::string input;
		size_t input_sent;
		std::map<std::string, std::string>& datamap;
	public:
		HandleCGI();
		HandleCGI(HandleCGI& copy);
		HandleCGI& operator=(HandleCGI& copy);
		~HandleCGI();
		void UpdateNewsLetter(const char *compiler, const char *script);
		void UpdateShowData(const char *compiler, const char *script);
		void HandleCGI::DoCGI(const char *cmd_list[3], EventMonitoring& em);
		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
		void string_to_map(std::string& data);
		void getQueryString(std::string& request, std::string& data);
};

#endif