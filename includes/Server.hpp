/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:40:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 14:30:11 by nfordoxc         ###   Luxembourg.lu     */
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
		std::list<Location>				_location;
	
		Server( const Server &src_obj );

		Server			&operator=( const Server &src_obj );

		bool			validate( void ) const;

	public:

		Server( char *filename );
		~Server( void );

		/*  SETTER  */
		void			setName( std::string &name);

		/*  GETTER  */
		std::string		getName( void ) const;

		/*	class Exception	*/
		class	ServerException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

#endif