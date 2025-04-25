/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/25 12:46:28 by nfordoxc         ###   Luxembourg.lu     */
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
		std::vector<Directive>				_directives;

		Location							&operator=( const Location &src_obj );

		void								parseData( std::string &data );
	
	public:

		Location( std::pair< const std::string, std::string> &data );
		Location( const Location &scr_obj );
		~Location( void );

		/*	GETTER	*/
		std::string							getName( void ) const;
		MethodHTTP							getMethod( void ) const;
		std::vector<Directive>				getDirectives( void ) const;

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif