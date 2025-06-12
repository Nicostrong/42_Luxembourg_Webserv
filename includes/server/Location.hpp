/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/11 09:23:28 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "../lib.hpp"
# include "../server/Directive.hpp"
# include "../server/MethodHTTP.hpp"
# include "../server/CGIDirective.hpp"

class	Token;

/*
 *	The Location object represents a location block in the server configuration.
 *	It contains the path of the location, the method allowed for this location
 *	and a list of directives that are specific to this location.
 *	We can check if a requested uri is valid for this location.
 *	We can get the path, the method and the directives of this location.
 */
class	Location
{
	private:

		std::string							_path;
		MethodHTTP*							_method;
		std::list<Directive*>				_lDirectives;
		std::list<CGIDirective*>			_lCGIDirectives;

		Location( const Location &scr_obj );

		Location							&operator=( const Location &src_obj );

		void								createLocation( Token*& tokens );
	
	public:

		Location( Token*& tokens );
		~Location( void );

		/*	GETTER	*/
		const std::string&					getPath( void ) const;
		const std::string&					getCGIPathExtension( const std::string& extension ) const;
		const std::string&					getCGIPathUri( const std::string& uri ) const;
		const std::string&					getDirectiveValue( const std::string& keyDir ) const;
		
		const MethodHTTP*					getMethod( void ) const;
		
		const std::list<Directive*>&		getDirectives( void ) const;

		const std::list<CGIDirective*>&		getCGIDirectives( void ) const;

		const Directive*					findDirective( const std::string& name ) const;

		const std::list<Directive*>			findDirectives( const std::string& name ) const;
		
		/*	CHECKER	*/
		bool								isMatching( const std::string& uri ) const;
		bool								isCGICDir( const std::string& extension ) const;

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif