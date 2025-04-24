/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:23 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/24 14:44:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLECONFIG_HPP
#define HANDLECONFIG_HPP

#include "lib.hpp"

class	HandleConfig
{
	private:

		std::map<std::string, std::string>	tmpMap;
		std::map<std::string, std::string>	nicoMap;
		
		HandleConfig( void );
		HandleConfig( HandleConfig &copy );
		HandleConfig	&operator=( HandleConfig &copy );

	public:

		HandleConfig( const char *filename );
		~HandleConfig( void );
		
		std::map<std::string, std::string>		getNicoMap( void );
		void									readConfigFile( const char *filename );
		void									cleanMap( void );
		void									printNicoMap( void );
		void									handleSimpleLine( std::string &line );
		void									handleObjLine( std::string &first, std::string &second );

};

#endif