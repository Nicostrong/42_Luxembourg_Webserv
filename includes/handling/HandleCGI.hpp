/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:42:18 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/19 15:29:40 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HandleCGI_HPP
# define HandleCGI_HPP

# include "../lib.hpp"
# include "../utils/Uri.hpp"
# include "../utils/Pipe.hpp"
# include "../utils/Buffer.hpp"
# include "../server/Location.hpp"
# include "../networking/Body.hpp"
# include "../events/IEventHandler.hpp"
# include "../events/EventMonitoring.hpp"

class	Socket;

class	HttpHandling;

class	HandleCGI: public IEventHandler
{
	private:

		Buffer									_txBuffer;
		Buffer									_rxBuffer;
		std::string								_output;
		std::string								_input;
		size_t									_input_sent;
		std::string								_data;
		char**									_aEnv;
		char**									_aCmd;
		std::map<std::string, std::string>		_mData;
		std::map<std::string, std::string>		_environmap;
		Socket*									_socket;
		bool									_endWrite;
		bool									_endRead;
		HttpHandling*							_handler;
		Pipe									_dataToCGI;
		Pipe									_dataFromCGI;

		HandleCGI( void );
		HandleCGI( const HandleCGI& copy );
		
		HandleCGI&		operator=( const HandleCGI& copy );

		void			string_to_map( void );
		void			map_to_chartab( void );
		void			initEnvironMapNULL( void );
		void			createCmdLst( Socket& socket );
		void			completeMyEnv( Socket& socket );

	public:
	
		HandleCGI( Socket& socket );
		~HandleCGI( void );

		char**			getCmd( void );
		char**			getEnv( void );
		
		void			DoCGI( Socket& socket );

		void			onReadEvent( int fd, int type, EventMonitoring& em );
		void			onWriteEvent( int fd, int type, EventMonitoring& em );
		void			onCloseEvent( int fd, int type, EventMonitoring& em );
		void 			onTickEvent( int fd, EventMonitoring& em );

};

#endif