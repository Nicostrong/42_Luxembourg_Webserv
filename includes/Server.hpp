/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:40:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/25 16:55:43 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
#  include "Location.hpp"

/*
 *	Server object contain all parameters from the server.conf file
 */
class	Server
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
		std::list<Location>				_location;

		Server( const Server &src_obj );
		Server							&operator=( const Server &src_obj );

		/*	SETTER	*/
		void							setAdress( std::string &data );
		void							setPort( std::string &data );
		void							setMaxSizeBody( std::string &data );
		void							setMapError( std::string &data );
		void							setLocation( std::string &name, std::string &block );
		
		/*	PARSER	*/
		void							parseData( const std::map< std::string, std::string> &data );

		/*	CHECKER	*/
		void							checkServer( void );
		
	public:
	
		// Simple Server Obj
		Server();
		Server( const std::map< std::string, std::string> &data );
		~Server( void );

		/*  GETTER  */
		size_t							getPort( void ) const;
		size_t							getMaxSizeBody( void ) const;

		std::string						getAdress( void ) const;
		std::string						getName( void ) const;
		std::string						getPath( void ) const;
		std::string						getIndex( void ) const;

		std::map<size_t, std::string>	getMapError( void ) const;
		std::list<Location>				getLocations( void ) const;
		
		// Functions For Checking Stuff for HandleRequest
		bool checkMethod(std::string data){(void)data; return (true);};
		bool checkUri(std::string data){(void)data; return (true);};
		bool checkHttpVersion(std::string data){(void)data; return (true);};
		bool checkBody(std::string data){(void)data; return (true);};

		template <typename T>
		void							setValue(T &target, std::string &data);

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