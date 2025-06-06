/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:42:18 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/06 09:11:39 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
# define HandleCGI_HPP

# include "../lib.hpp"
# include "../utils/Pipe.hpp"
# include "../networking/BodyParser.hpp"
# include "../networking/Socket.hpp"
# include "../events/EventMonitoring.hpp"
# include "../events/IEventHandler.hpp"

class HandleCGI: public IEventHandler
{
	private:
		BodyParser*								bp;
		std::vector<char>						receivedTxtBuffer;
		std::string								output;
		std::string								input;
		size_t									input_sent;
		std::string								data;
		char**									newenviron;
		std::map<std::string, std::string>		datamap;
		std::map<std::string, std::string>		environmap;
		HandleCGI();
	public:
		
		HandleCGI(*cmd_list[3], EventMonitoring& em, std::string& data, Socket& socket);
		HandleCGI(HandleCGI& copy);
		HandleCGI& operator=(HandleCGI& copy);
		~HandleCGI();
		void 			UpdateNewsLetter(const char *compiler, const char *script, const char *newvalue);
		void 			UpdateShowData(const char *compiler, const char *script, const char *newvalue);
		void 			DoCGI(const char *cmd_list[3], EventMonitoring& em);
		void 			onReadEvent(int fd, int type, EventMonitoring& em);
		void 			onWriteEvent(int fd, int type, EventMonitoring& em);
		void 			onCloseEvent(int fd, int type, EventMonitoring& em);
		void 			string_to_map();
		char * const*	map_to_chartab();
		void 			initEnvironMapNULL();
		void			completeEnvironMap( Socket& socket );
};

#endif