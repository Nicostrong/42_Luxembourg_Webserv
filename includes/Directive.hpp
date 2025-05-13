/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:17:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:23:40 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_HPP
# define DIRECTIVE_HPP

# include "lib.hpp"

/*
 *  Directive object for 
 */
class	Directive
{

	private:

		std::string					_key;
		std::string					_value;

		Directive( const Directive &src_obj );
		Directive					&operator=( const Directive &src_obj );

	public:

		Directive( std::string &key, std::string &value );
		~Directive( void );

		/*  GETTER  */
		std::string					getKey( void ) const;
		std::string					getValue( void ) const;

		/*	class Exception	*/
		class	DirectiveException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};

		/*	fields empty	*/
		class	FieldsEmpty : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, const Directive &src_object );

#endif