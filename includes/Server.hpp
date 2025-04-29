/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/29 14:43:21 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# include "Location.hpp"
# include "EventMonitoring.hpp"
# include "IEventHandler.hpp"
# include "Socket.hpp"

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
		std::string						_adress;
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
		void							setAdress( std::string &data );
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

		Server( EventMonitoring &eventMonitoring );
		Server( const std::map< std::string, std::string> &data,
				EventMonitoring &eventMonitoring );
		~Server( void );

		/*  GETTER  */
		int								getMaxConnectionClient( void ) const;

		size_t							getPort( void ) const;
		size_t							getMaxSizeBody( void ) const;

		std::string						getAdress( void ) const;
		std::string						getName( void ) const;
		std::string						getPath( void ) const;
		std::string						getIndex( void ) const;

		std::map<size_t, std::string>	getMapError( void ) const;
		std::list<Location *>			getLocations( void ) const;
		
		/*	Checker GIGI	*/
		bool							checkUri( std::string uri );
		bool							checkMethod( std::string uri,
													std::string method );

		/*	Template function for Server setting	*/
		template <typename T>
		void							setValue(T &target, std::string &data);

		// Server exec related
		void 							start( void );
		void 							onReadEvent( int fd, int type );
		void 							onWriteEvent( int fd, int type );
		void 							onCloseEvent( int fd, int type );
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