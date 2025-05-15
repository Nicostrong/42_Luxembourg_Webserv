/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:17:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 10:48:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_HPP
# define DIRECTIVE_HPP

# include "lib.hpp"

/*
 *  The Directive object represents a directive of the server [key]:value.
 *  With this object, you can get the key and the value of the directive.
 *  The key is the name of the directive and the value is the value of the
 *  directive.
 */
class	Directive
{

	private:

		std::string					_key;
		std::list<std::string>		_lValue;

		Directive( const Directive& src_obj );
		Directive&					operator=( const Directive& src_obj );

	public:

		Directive( Token*& directiveTokens );
		~Directive( void );

		/*  GETTER  */
		const std::string&			getKey( void ) const;
		const std::string&			getValue( void ) const;

		/*	class Exception	*/
		/*	fields empty	*/
		class	FieldsEmpty : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, const Directive &src_object );

#endif