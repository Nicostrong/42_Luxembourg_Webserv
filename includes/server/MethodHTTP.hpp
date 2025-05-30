/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/30 14:36:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODHTTP_HPP
# define METHODHTTP_HPP

# include "../lib.hpp"

class	Token;

class	MethodHTTP
{

	private:

		std::set<std::string>			_allowed;
		static std::set<std::string>	_validMethods;
		static std::set<std::string>	_implementedMethods;

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
		static std::set<std::string>	initImplementedMethods( void );
		
		/*	GETTER	*/
		const std::string				getAllowed( void ) const;

		/*	METHODE	*/
		static bool						isMethod( const std::string& method );
		static bool						isMethodImplemented( const std::string &method );
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