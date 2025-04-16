/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:10 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 15:03:06 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "lib.hpp"
# include "Directive.hpp"

/*
 *  LocationConfig object for
 */
class	Location
{
	private:

		enum								Methods
		{
			GET,
			POST,
			PUT,
			DELETE,
			PATCH,
			OPTIONS,
			HEAD
		};
		
		bool								_autoIndex;
		std::string							_rootPath;
		std::string							_returnPath;
		std::list<Methods>					_methodOk;
		std::list<Methods>					_methodDeny;
		std::map<std::string, Directive>	_directives;

		Location( const Location &scr_obj );

		Location	&operator=( const Location &src_obj );

		bool		validate( void ) const;
	
	public:

		Location( void );
		~Location( void );

		/*	class Exception	*/
		class	LocationException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

#endif