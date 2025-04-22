/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 18:19:07 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODHTTP_HPP
# define METHODHTTP_HPP

# include "lib.hpp"

class	MethodHTTP
{

	private:

		std::set<std::string>			_allowed;
		std::set<std::string>			_denied;

		static std::set<std::string>	_validMethods;

		bool							isMethod( const std::string &method ) const;

# ifndef TEST
		static std::set<std::string>	initValidMethods( void );
# endif

		void							parse( const std::string &data );

	public:

		MethodHTTP( void );
		MethodHTTP( const std::string &data );
		MethodHTTP( const MethodHTTP &src_obj );
		~MethodHTTP( void );

		MethodHTTP						&operator=( const MethodHTTP &src_obj );

# ifdef TEST
		static std::set<std::string>	initValidMethods( void );
# endif

		/*	SETTER	*/
		void							allow( const std::string &method );
		void							deny( const std::string &method );

		/*	GETTER	*/
		std::string						getAllowed( void ) const;
		std::string						getDenied( void ) const;

		/*	METHODE	*/
		void							clear( void );
		bool							isAllowed( const std::string &method ) const;
		bool							isDenied( const std::string &method ) const;

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