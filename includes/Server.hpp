/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:00 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:17:47 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */



#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# include "Token.hpp"
# include "Socket.hpp"
# include "Location.hpp"
# include "Directive.hpp"
# include "Ressource.hpp"
# include "IEventHandler.hpp"
# include "EventMonitoring.hpp"

/*
 *	Server object contain all parameters from the server.conf file
 */
class	Server : public IEventHandler
{
	
	private:

		int										_maxClient;
		int										_serverSocket;
		size_t									_port;
		size_t									_maxSizeBody;
		std::string								_name;
		std::string								_path;
		std::string								_index;
		std::map<size_t, std::string>			_mError;
		std::map<std::string, Location *>		_mLocations;
		std::list<Directive *>					_lDirectives;
		std::list<Socket>						_lSockets;
		EventMonitoring&						_em;

		Server( const Server &src_obj );
		Server									&operator=( const Server &src_obj );

		/*	SETTER	*/
		void									setPort( std::string data );
		void									setMaxSizeBody( std::string data );
		void									setMaxClient( std::string data );
		
		/*	Token	*/
		void									setAttributs( void );
		void									createError( Token* tokens );
		void									createServer( Token* tokens );
		void									createDirective( Token* tokens );

		/* Cleanup func to close all sockets(server included)*/
		void									cleanup( void );
		/*	Check the value of port and */
		void									checkServer( void );
		
	public:

		Server( EventMonitoring& eventMonitoring );
		Server( const std::map< std::string, std::string>& data,
				EventMonitoring& eventMonitoring );
		Server( Token* serverTokensConfig, EventMonitoring& eventMonitoring );
		~Server( void );

		/*  GETTER	*/
		const int&								getMaxClient( void ) const;

		const size_t&							getPort( void ) const;
		const size_t&							getMaxSizeBody( void ) const;

		const std::string&						getName( void ) const;
		const std::string&						getPath( void ) const;
		const std::string&						getIndex( void ) const;
		const std::string						getPathError( size_t error_code ) const;

		const std::map<size_t, std::string>&	getMapError( void ) const;
		const std::map<std::string, Location *>	getAllLocation( void ) const;
		const Location&							getLocations( std::string path ) const;

		/*	Checker GIGI	*/
		bool									checkUri( std::string uri );
		const Location*							getUri( const std::string& uri );
		bool									checkMethod( std::string uri,
															std::string method );

		/*	Server exec related	*/
		void 									start( void );
		void 									onReadEvent( int fd, int type, 
															EventMonitoring& em );
		void 									onWriteEvent( int fd, int type, 
															EventMonitoring& em );
		void 									onCloseEvent( int fd, int type, 
															EventMonitoring& em );
		void 									onSocketClosedEvent( const Socket &s );

		/*	EXCEPTION	*/
		/*	server error Exception	*/
		class	ServerException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};

		/*	parsing error Exception	*/
		class	ParsingError: public std::exception
		{

			private:

				std::string				_msg;

			public:

				ParsingError( const std::string &data ) throw();
				virtual ~ParsingError( void ) throw();
				virtual const char	*what() const throw();
		
		};

		/*	port value error Exception	*/
		class	PortValueException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
		
};

std::ostream	&operator<<( std::ostream &out, Server const &src_object );

#endif