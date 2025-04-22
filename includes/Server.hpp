/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:40:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 18:06:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# ifndef TEST
#  include "Location.hpp"
# endif

/*
 *	Server object contain all parameters from the server.conf file
 */
class	Server
{
	
	private:

		size_t							_port;
		size_t							_maxSizeBody;
		std::string						_name;
		std::string						_adress;
		std::string						_path;
		std::string						_index;
		std::map<size_t, std::string>	_mError;
# ifndef TEST
		std::list<Location>				_location;
# endif

		Server( const Server &src_obj );
		Server							&operator=( const Server &src_obj );

		/*	SETTER	*/
		void							setAdress( std::string &data );
		void							setPort( std::string &data );
		void							setName( std::string &data );
		void							setPath( std::string &data );
		void							setIndex( std::string &data );
		void							setMaxSizeBody( std::string &data );
		void							setMapError( std::string &data );
# ifndef TEST
		void							setLocation( std::string &name, std::string &block );
# endif
		
	public:

		Server( std::map< std::string, std::string> const &data );
		~Server( void );

		/*  GETTER  */
		size_t							getPort( void ) const;
		size_t							getMaxSizeBody( void ) const;

		std::string						getAdress( void ) const;
		std::string						getName( void ) const;
		std::string						getPath( void ) const;
		std::string						getIndex( void ) const;

		std::map<size_t, std::string>	getMapError( void ) const;

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