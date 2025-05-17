/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:40:43 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:34:35 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIDIRECTIVE_HPP
# define CGIDIRECTIVE_HPP

# include "../lib.hpp"
# include "../parser/Token.hpp"

class	CGIDirective
{

	private:

		std::string				_extension;
		std::string				_path;

		CGIDirective( const CGIDirective& src_obj );
		CGIDirective&			operator=( const CGIDirective& src_obj );

	public:

		CGIDirective( Token*& tokens );
		~CGIDirective( void );
		/*  GETTER  */
		const std::string&		getPath( void ) const;
		const std::string&		getExtension( void ) const;

		/*	class Exception	*/
		/*	fields empty	*/
		class	FieldsEmpty : public std::exception
		{

			public:

				const char*	what() const throw();

		};

		/*	bad token type	*/
		class	BadTokenType : public std::exception
		{

			public:

				const char*	what() const throw();

		};

};

std::ostream	&operator<<( std::ostream& out, const CGIDirective& src_object );

#endif