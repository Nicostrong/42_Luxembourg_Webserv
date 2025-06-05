/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:42:18 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/05 14:49:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
#define HandleCGI_HPP

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include "Pipe.hpp"
#include "BodyParsing.hpp"

class HandleCGI: public IEventHandler
{
	private:
		BodyParser *bp;
		std::vector<char> receivedTxtBuffer;
		std::string output;
		std::string input;
		size_t input_sent;
		std::string data;
		std::map<std::string, std::string> datamap;
		std::map<std::string, std::string> environmap;
	public:
		HandleCGI();
		HandleCGI(std::string& data);
		HandleCGI(HandleCGI& copy);
		HandleCGI& operator=(HandleCGI& copy);
		~HandleCGI();
		void UpdateNewsLetter(const char *compiler, const char *script);
		void UpdateShowData(const char *compiler, const char *script);
		void HandleCGI::DoCGI(const char *cmd_list[3], EventMonitoring& em);
		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
		void string_to_map();
		char * const* map_to_chartab();
		void initEnvironMapNULL();
		void	completeEnvironMap( const Socket& socket );
};

#endif