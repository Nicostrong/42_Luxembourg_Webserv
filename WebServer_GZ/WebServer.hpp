/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:23 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/17 14:14:32 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <iostream>
#include <fstream>
#include <map>

class WebServer
{
	private:
		//std::map<std::string, std::map<std::string, std::string>> globalmap;
	public:
		void readConfigFile(const char *filename) const;
};

#endif