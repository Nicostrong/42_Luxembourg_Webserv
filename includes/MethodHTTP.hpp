/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/11 16:41:00 by nicostrong       ###   Luxembourg.lu     */
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

		void							initDefault( void );

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
		static bool						isMethod( const std::string &method );
		bool							isDenied( const std::string &method ) const;
		bool							isAllowed( const std::string &method ) const;

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