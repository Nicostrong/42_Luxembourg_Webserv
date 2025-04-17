/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 14:14:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "lib.hpp"
# include "Directive.hpp"
# include "MethodesHTTP.hpp"

/*
 *  LocationConfig object for
 */
class	Location
{
	private:

	
		bool								_autoIndex;
		std::string							_rootPath;
		std::string							_returnPath;
		std::list<MethodesHTTP>				_methodOk;
		std::list<MethodesHTTP>				_methodDeny;
		std::map<std::string, Directive>	_directives;

		Location( const Location &scr_obj );

		Location							&operator=( const Location &src_obj );

		bool								validate( void ) const;
	
	public:

		Location( std::map<std::string, std::string> &data );
		~Location( void );

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Location const &src_object );

#endif