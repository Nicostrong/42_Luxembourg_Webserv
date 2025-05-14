/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 11:12:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODHTTP_HPP
# define METHODHTTP_HPP

# include "lib.hpp"

class	Token;

class	MethodHTTP
{

	private:

		std::set<std::string>			_allowed;
		static std::set<std::string>	_validMethods;

		MethodHTTP( const MethodHTTP& src_obj );

		MethodHTTP						&operator=( const MethodHTTP& src_obj );

		void							initDefault( void );

		/*	SETTER	*/
		void							allowAll( void );
		void							allow( const std::string& method );

	public:
	
		MethodHTTP( void );
		MethodHTTP( Token*& tokens );
		~MethodHTTP( void );

		static std::set<std::string>	initMethods( void );
		
		/*	GETTER	*/
		const std::string				getAllowed( void ) const;

		/*	METHODE	*/
		static bool						isMethod( const std::string& method );
		bool							isAllowed( const std::string& method ) const;

		/*	Unknow method exception	*/
		class	MethodUnknow: public std::exception
		{

			private:

				std::string				_msg;

			public:

				MethodUnknow( const std::string &method ) throw();
				virtual ~MethodUnknow( void ) throw();
				virtual const char	*what() const throw();
		
		};
		
};

std::ostream	&operator<<( std::ostream &out, MethodHTTP const &src_object );

#endif