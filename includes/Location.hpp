/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:19:32 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "lib.hpp"
# include "Directive.hpp"
# include "MethodHTTP.hpp"

class	Token;

/*
 *  LocationConfig object for
 */
class	Location
{
	private:

		std::string							_path;
		MethodHTTP*							_method;
		std::list<Directive *>				_lDirectives;

		Location							&operator=( const Location &src_obj );

		void								parseData( std::string &data );
		void								createLocation( Token* tokens );
	
	public:

		Location( Token* tokens );
		Location( const Location &scr_obj );
		~Location( void );

		/*	GETTER	*/
		std::string							getPath( void ) const;
		MethodHTTP							*getMethod( void ) const;
		const std::list<Directive *>&		getDirectives( void ) const;
		/*std::string							buildUriOnServer(std::string uri) 
			const;*/
		bool								isMatching(const std::string& uri) 
			const;

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif