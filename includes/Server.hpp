/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:00 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/12 16:06:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */



#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# include "Location.hpp"
# include "EventMonitoring.hpp"
# include "IEventHandler.hpp"
# include "Socket.hpp"
# include "Ressource.hpp"
# include "Token.hpp"

/*
 *	Server object contain all parameters from the server.conf file
 */
class	Server : public IEventHandler
{
	
	private:

		size_t							_port;
		int								_maxConnectionClient;
		size_t							_maxSizeBody;
		std::string						_name;
		std::string						_path;
		std::string						_index;
		std::map<size_t, std::string>	_mError;
		std::list<Location *>			_location;
		EventMonitoring&				_em;
		int								_serverSocket;
		std::list<Socket>				_sockets;

		Server( const Server &src_obj );
		Server							&operator=( const Server &src_obj );

		/*	SETTER	*/
		void							setPort( std::string &data );
		void							setMaxSizeBody( std::string &data );
		void							setMapError( std::string &data );
		void							setLocation( std::string &name,
													std::string &block );
		
		/*	PARSER	*/
		void							parseData( const std::map< std::string,
														std::string> &data );

		/*	CHECKER	*/
		void							checkServer( void );

		/* Cleanup func to close all sockets(server included)*/
		void							cleanup( void );
		
	public:

		Server( EventMonitoring& eventMonitoring );
		Server( const std::map< std::string, std::string>& data,
				EventMonitoring& eventMonitoring );
		Server( Token* serverTokensConfig, EventMonitoring& eventMonitoring );
		~Server( void );

		/*  GETTER	*/
		const int&								getMaxConnectionClient( void ) const;

		const size_t&							getPort( void ) const;
		const size_t&							getMaxSizeBody( void ) const;

		const std::string&						getName( void ) const;
		const std::string&						getPath( void ) const;
		const std::string&						getIndex( void ) const;
		const std::string						getPathError( size_t error_code ) const;

		const std::map<size_t, std::string>&	getMapError( void ) const;
		const std::list<Location *>&			getLocations( void ) const;
		
		/*	Checker GIGI	*/
		bool									checkUri( std::string uri );
		const Location*							getUri( const std::string& uri );
		bool									checkMethod( std::string uri,
																std::string method );

		/*	Template function for Server setting	*/
		template <typename T>
		void							setValue(T &target, std::string &data);

		/*	Server exec related	*/
		void 							start( void );
		void 							onReadEvent( int fd, int type, 
														EventMonitoring& em );
		void 							onWriteEvent( int fd, int type, 
														EventMonitoring& em );
		void 							onCloseEvent( int fd, int type, 
														EventMonitoring& em );
		void 							onSocketClosedEvent( const Socket &s );

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