/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodesHTTP.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 16:11:07 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODESHTTP_HPP
# define METHODESHTTP_HPP

# include "lib.hpp"

class	MethodesHTTP
{

	private:

		std::set<std::string>			_allowed;
		std::set<std::string>			_denied;

		static std::set<std::string>	_validMethodes;

		MethodesHTTP( const MethodesHTTP &src_obj );
		MethodesHTTP					&operator=( const MethodesHTTP &src_obj );

		bool							isMethode( const std::string &methode ) const;

		static std::set<std::string>	initValidMethodes( void );

	public:

		MethodesHTTP( void );
		~MethodesHTTP( void );

		/*	SETTER	*/
		void							allow( const std::string &methode );
		void							deny( const std::string &methode );

		/*	GETTER	*/
		std::string						getAllowed( void ) const;
		std::string						getDenied( void ) const;

		/*	METHODE	*/
		void							clear( void );
		bool							isAllowed( const std::string &methode ) const;
		bool							isDenied( const std::string &methode ) const;

		/*	class Exception	*/
		class	MethodeUnknowException : public std::exception
		{

			public:

				const char	*what() const throw();

		};
		
};

std::ostream	&operator<<( std::ostream &out, MethodesHTTP const &src_object );
std::set<std::string>	MethodesHTTP::_validMethodes = MethodesHTTP::initValidMethodes();

#endif