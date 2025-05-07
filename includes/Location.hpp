/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/07 23:12:10 by fdehan           ###   ########.fr       */
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
		MethodHTTP*							_method;
		std::list<Directive *>				_directives;

		Location							&operator=( const Location &src_obj );

		void								parseData( std::string &data );
	
	public:

		Location( std::pair< const std::string, std::string> &data );
		Location( const Location &scr_obj );
		~Location( void );

		/*	GETTER	*/
		std::string							getName( void ) const;
		MethodHTTP							*getMethod( void ) const;
		const std::list<Directive *>&		getDirectives( void ) const;
		bool								isMatching(const std::string& uri) 
			const;
		const	Directive* 					findDirective(
			const std::string& name) const;

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif