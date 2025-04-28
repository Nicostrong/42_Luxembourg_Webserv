/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:23 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/28 15:15:50 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLECONFIG_HPP
#define HANDLECONFIG_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class HandleConfig
{
	private:
		std::map<std::string, std::string> tmpMap;
		std::map<std::string, std::string> webconfMap;
	public:
		HandleConfig(const char *filename);
		HandleConfig(HandleConfig& copy);
		HandleConfig& operator=(HandleConfig& copy);
		HandleConfig();
		~HandleConfig();
		std::map<std::string, std::string>& getwebconfMap();
		void readConfigFile(const char *filename);
		void cleanMap();
		void printwebconfMap();
		void handleSimpleLine(std::string& line);
		void handleObjLine(std::string& first, std::string& second);
		std::string& getValue(std::string key);
};

#endif