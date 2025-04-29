/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:23 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/29 13:10:28 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLECONFIG_HPP
#define HANDLECONFIG_HPP

#include "lib.hpp"
#include <sstream>

class	HandleConfig
{
	private:

		std::map<std::string, std::string>	tmpMap;
		std::map<std::string, std::string>	webconfMap;
		
	public:
		HandleConfig(void);
		HandleConfig( const char *filename );
		HandleConfig( HandleConfig &copy );
		HandleConfig	&operator=( HandleConfig &copy );
		~HandleConfig( void );
		
		std::map<std::string, std::string>		getwebconfMap( void );
		void									readConfigFile( const char *filename );
		void									cleanMap( void );
		void									printwebconfMap( void );
		void									handleSimpleLine( std::string &line );
		void									handleObjLine( std::string &first, std::string &second );

};

#endif