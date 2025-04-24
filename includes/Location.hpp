/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/23 08:59:06 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "lib.hpp"
# include "Directive.hpp"
# include "MethodHTTP.hpp"

/*
 *  LocationConfig object for
 */
class	Location
{
	private:

		std::string							_name;
		MethodHTTP							_method;
		std::map<std::string, Directive>	_directives;

		Location( const Location &scr_obj );
		Location							&operator=( const Location &src_obj );
	
	public:

		Location( std::pair< const std::string, std::string> &data );
		~Location( void );

		/*	GETTER	*/
		std::string							getName( void ) const;
		MethodHTTP							getMethod( void ) const;
		std::map<std::string, Directive>	getDirectives( void ) const;

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif