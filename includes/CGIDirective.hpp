/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:40:43 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 14:53:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIDIRECTIVE_HPP
# define CGIDIRECTIVE_HPP

# include "./lib.hpp"

class	CGIDirective
{

	private:

		std::string				_extension;
		std::string				_path;

		CGIDirective( const CGIDirective& src_obj );
		CGIDirective&			operator=( const CGIDirective& src_obj );

	public:

		CGIDirective( std::string &extension, std::string &path );
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

};

std::ostream	&operator<<( std::ostream& out, const CGIDirective& src_object );
