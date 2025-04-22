/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:17:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 08:22:07 by nfordoxc         ###   Luxembourg.lu     */
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

		std::string					_name;
		std::vector<std::string>	_values;
	
		Directive( const Directive &src_obj );
		Directive					&operator=( const Directive &src_obj );

	public:

		Directive( std::string &data );
		~Directive( void );

		/*  SETTER  */
		void						setName( std::string &name);
		void						setValue( size_t index, std::string &value );
		void						addValue( std::string &value );

		/*  GETTER  */
		std::string					getName( void ) const;
		std::string					getValue( int index ) const;
		std::string					getAllValue( void ) const;

		/*	class Exception	*/
		class	DirectiveException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

std::ostream	&operator<<( std::ostream &out, Directive &src_object );

#endif