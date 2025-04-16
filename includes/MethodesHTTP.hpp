/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodsHTTP.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:34:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 15:24:29 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODESHTTP_HPP
# define METHODESHTTP_HPP

# include "lib.hpp"

class	MethodesHTTP
{

	private:

		std::set<std::string>				_allowed;
		std::set<std::string>				_denied;

		static const std::set<std::string>	_validMethodes;

		MethodesHTTP( const MethodesHTTP &src_obj );
		MethodesHTTP	&operator=( const MethodesHTTP &src_obj );

		bool			isMethode( const std::string &methode ) const;

		void			initValidMethodes( void );

	public:

		MethodesHTTP( void );
		~MethodesHTTP( void );

		/*	SETTER	*/
		void			allow( const std::string &methode );
		void			deny( const std::string &methode );

		/*	GETTER	*/
		bool			isAllowed( const std::string &methode ) const;
		bool			isDenied( const std::string &methode ) const;

		/*	METHODE	*/
		void			clear( void );

		/*	class Exception	*/
		class	MethodeUnknowException : public std::exception
		{

			public:

				const char	*what() const throw();

		};
		
};

#endif