/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:00 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 13:21:50 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */



#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# include "Uri.hpp"
# include "Token.hpp"
# include "Socket.hpp"
# include "Location.hpp"
# include "Directive.hpp"
# include "Ressource.hpp"
# include "IEventHandler.hpp"
# include "EventMonitoring.hpp"

/*
 *	The Server object represents the configuration of a server that listens on 
 *	a specific port.
 *	With this object, you can get some information about the server, like the
 *	name, the path, the index file, the max size of body, the max number of
 *	client, the error pages and the locations.
 *	You can also check if a requested uri is valid and if the method is allowed
 *	for this uri.
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
		std::string								_serverIp;

		EventMonitoring&						_em;

		Server( const Server &src_obj );
		Server									&operator=( const Server &src_obj );

		/*	SETTER	*/
		void									setPort( std::string data );
		void									setMaxSizeBody( std::string data );
		void									setMaxClient( std::string data );
		
		/*	Token	*/
		void									setAttributs( void );
		void									createError( Token*& tokens );
		void									createServer( Token*& tokens );
		void									createDirective( Token*& tokens );

		/* Cleanup func to close all sockets(server included)*/
		void									cleanup( void );
		
	public:

		Server( Token*& serverTokensConfig, EventMonitoring& eventMonitoring );
		~Server( void );

		/*  GETTER	*/
		const int&								getMaxClient( void ) const;

		const size_t&							getPort( void ) const;
		const size_t&							getMaxSizeBody( void ) const;

		const std::string&						getName( void ) const;
		const std::string&						getPath( void ) const;
		const std::string&						getIndex( void ) const;
		const std::string&						getPathError( size_t error_code ) const;

		const std::map<size_t, std::string>&	getMapError( void ) const;
		const std::map<std::string, Location *>	getAllLocation( void ) const;
		const Location&							getLocations( std::string path ) const;

		/*	CHECKER	*/
		bool									checkUri( std::string uri );
		const Location*							getMatchingLoc( const std::string& uri );
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