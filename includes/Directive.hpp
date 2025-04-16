/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:17:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 14:29:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_HPP
# define DIRECTIVE_HPP

# include "lib.hpp"

/*
 *  Directive object for 
 */
class   Directive
{

	private:

		std::string					_name;
		std::vector<std::string>	_values;
	
		Directive( const Directive &src_obj );
		Directive	&operator=( const Directive &src_obj );

		bool		validate( void ) const;

	public:

		Directive( void );
		~Directive( void );

		/*  SETTER  */
		void		setName( std::string &name);

		/*  GETTER  */
		std::string	getName( void ) const;

		/*	class Exception	*/
		class	DirectiveException : public std::exception
		{

			public:

				const char	*what() const throw();
		
		};
};

#endif