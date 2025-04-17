/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:40:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 13:46:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "lib.hpp"
# include "Location.hpp"


/*
 *	Server object
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
		//std::list<Location>				_location;
	
		Server( const Server &src_obj );

		Server							&operator=( const Server &src_obj );

		/*	PRIVATE METHODE	*/
		//bool							validate( void ) const;

		/*	SETTER	*/
		void							setPort( std::string &data );
		void							setMaxSizeBody( std::string &data );
		void							setName( std::string &data );
		void							setAdress( std::string &data );
		void							setPath( std::string &data );
		void							setIndex( std::string &data );
		void							setMapError( std::string &data );
		void							setLocation( std::string &data );
		
	public:

		Server( const std::string &filename );
		~Server( void );

		/*  GETTER  */
		size_t							getPort( void ) const;
		size_t							getMaxSizeBody( void ) const;
		std::string						getName( void ) const;
		std::string						getAdress( void ) const;
		std::string						getPath( void ) const;
		std::string						getIndex( void ) const;
		//void							getMapError( void ) const;
		//void							getLocation( void ) const;

		/*	METHODE	*/
		void							initServer( const std::string &data );

		/*	server error Exception	*/
		class	ServerException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};

		/*	open file.conf fail Exception	*/
		class	OpenConfFailException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};

		/*	parsing error Exception	*/
		class	ParsingErrorException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Server const &src_object );

#endif