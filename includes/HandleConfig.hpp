/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:23 by gzenner           #+#    #+#             */
/*   Updated: 2025/05/17 11:42:32 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLECONFIG_HPP
#define HANDLECONFIG_HPP

#include "./lib.hpp"

class HandleConfig
{
	private:
		std::map<std::string, std::string> tmpMap;
		std::map<std::string, std::string> webconfMap;
        std::vector<std::string> config_vec;
        std::string configfilename;
	public:
		HandleConfig();
		HandleConfig(const char *filename);
		HandleConfig(const HandleConfig& copy);
		HandleConfig& operator=(const HandleConfig& copy);
		~HandleConfig();

        std::map<std::string, std::string>		getwebconfMap( void );
		void									genTmpMap();
		void									genWebconfMap( void );
		void									printwebconfMap( void );
		void									handleSimpleLine( std::string &line );
		void									handleObjLine( std::string &first, std::string &second );
		void									saveRawConfig(const char *filename);
		std::string&                            getValue(std::string key);
};

#endif