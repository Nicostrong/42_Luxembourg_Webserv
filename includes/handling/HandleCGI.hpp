/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:42:18 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/06 14:43:43 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
# define HandleCGI_HPP

# include "../lib.hpp"
# include "../utils/Uri.hpp"
# include "../utils/Pipe.hpp"
# include "../server/Location.hpp"
# include "../networking/Socket.hpp"
# include "../events/IEventHandler.hpp"
# include "../networking/BodyParser.hpp"
# include "../events/EventMonitoring.hpp"

class HandleCGI: public IEventHandler
{
	private:

		//BodyParser*								bp;
		std::vector<char>						receivedTxtBuffer;
		std::string								output;
		std::string								input;
		size_t									input_sent;
		std::string								data;
		char**									newenviron;
		char**									lCmd;
		std::map<std::string, std::string>		datamap;
		std::map<std::string, std::string>		environmap;
		HandleCGI();
		void									createCmdLst( Socket& socket );

	public:
	
		HandleCGI(Socket& socket);
		HandleCGI(HandleCGI& copy);
		HandleCGI& operator=(HandleCGI& copy);
		~HandleCGI();
		void 			UpdateNewsLetter(const char *compiler, const char *script, const char *newvalue);
		void 			UpdateShowData(const char *compiler, const char *script, const char *newvalue);
		void 			DoCGI( Socket& socket );
		void 			onReadEvent(int fd, int type, EventMonitoring& em);
		void 			onWriteEvent(int fd, int type, EventMonitoring& em);
		void 			onCloseEvent(int fd, int type, EventMonitoring& em);
		void 			string_to_map();
		char * const*	map_to_chartab();
		void 			initEnvironMapNULL();
		void			completeEnvironMap( Socket& socket );
};

#endif