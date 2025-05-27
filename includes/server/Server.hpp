/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:00 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/27 08:56:43 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../lib.hpp"
# include "../Socket.hpp"
# include "../Ressource.hpp"
# include "../parser/Token.hpp"
# include "../IEventHandler.hpp"
# include "../EventMonitoring.hpp"
# include "../server/Location.hpp"
# include "../server/Directive.hpp"

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
		size_t									_maxSizeBody;
		std::string								_path;
		std::string								_index;
		std::string								_serverIp;
		std::list<size_t>						_lPorts;
		std::list<std::string>					_lHost;
		std::list<Directive *>					_lDirectives;
		std::list<Socket>						_lSockets;
		std::map<size_t, std::string>			_mError;
		std::map<std::string, Location *>		_mLocations;
		EventMonitoring&						_em;

		Server( const Server &src_obj );
		Server		&operator=( const Server &src_obj );

		/*	SETTER	*/
		void		setPort( std::list<std::string> datalist );
		void		setMaxSizeBody( std::string data );
		void		setMaxClient( std::string data );
		
		/*	Token	*/
		void		setAttributs( void );
		void		createError( Token*& tokens );
		void		createServer( Token*& tokens );

		/*	CHECKER	*/
		bool		matchServerName( const std::string& host ) const;
		bool		matchServerNameWildcard( const std::string& host ) const;

		/* Cleanup func to close all sockets(server included)*/
		void		cleanup( void );
		
	public:

		Server( Token*& serverTokensConfig, EventMonitoring& eventMonitoring );
		~Server( void );

		/*  GETTER	*/
		const int&				getMaxClient( void ) const;

		const size_t&			getMaxSizeBody( void ) const;

		const std::string&		getPath( void ) const;
		const std::string&		getIndex( void ) const;
		const std::string&		getServerIp( void ) const;
		const std::string&		getPathError( size_t error_code ) const;

		const std::list<size_t>&		getPortList( void ) const;

		const std::list<std::string>&		getHost( void ) const;

		const std::map<size_t, std::string>&		getMapError( void ) const;
		const std::map<std::string, Location *>		getAllLocation( void ) const;

		const Location&		getLocations( std::string path ) const;
		const Location*		getMatchingLoc( const std::string& uri );
		std::string			getLocIndex( const Location* loc );

		/*	CHECKER	*/
		bool		checkUri( std::string uri );
		bool		matchHost( const std::string& host ) const;
		bool		checkMethod( std::string uri, std::string method );


		/*	Server exec related	*/
		void		start( void );
		void 		onReadEvent( int fd, int type, EventMonitoring& em );
		void 		onWriteEvent( int fd, int type, EventMonitoring& em );
		void 		onCloseEvent( int fd, int type, EventMonitoring& em );
		void 		onSocketClosedEvent( const Socket &s );

		/*	EXCEPTION	*/
		/*	parsing error Exception	*/
		class	ParsingError: public std::exception
		{

			private:

				std::string		_msg;

			public:

				ParsingError( const std::string &data ) throw();
				virtual ~ParsingError( void ) throw();
				virtual const char*		what() const throw();
		
		};

		/*	port value error Exception	*/
		class	PortValueException : public std::exception
		{

			public:

				const char*		what() const throw();
		
		};
		
};

std::ostream	&operator<<( std::ostream &out, Server const &src_object );

#endif