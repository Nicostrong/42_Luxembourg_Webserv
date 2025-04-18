/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/17 16:22:52 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include <vector>
#include <stdio.h>
#include <string.h>

void WebServer::readConfigFile(const char *filename) const
{
	std::vector<std::string> vector;
	std::ifstream file(filename);
	//std::ofstream ofile("tmp.txt");
	std::size_t found;
	bool insideObj = false;

	if (!file.is_open())
	{
        std::cerr << "Error opening file " << filename << std::endl;
        return ;
    }
	std::string line;
	while(getline(file, line))
	{
		vector.push_back(line);
		/*std::string firstEl;
		std::string secondEl;
		std::map<std::string, std::string> tmp;
		found = line.find(" ");
		if (found != std::string::npos)
		{
			firstEl = line.substr(0, found);
		}
		//line = line.substr(found, line.size());
		int i = 0;
		secondEl = line.substr(i, line.size());
		std::cout << "[debug]" << firstEl << " " << secondEl << "\n";*/
	}
	
	for(int i = 1; i < vector.size(); i++)
	{
		found = vector[i].find('{');
		if (found == std::string::npos)
		{
			if(!insideObj)
			{
				std::cout << vector[i] << "\n===\n";
				std::ofstream otmp("otmp.txt");
				otmp << vector[i];
				otmp.close();
				std::ifstream itmp("otmp.txt");
				std::string firstEl;
				std::string secondEl;
				itmp >> firstEl;
				itmp >> secondEl;
				std::map<std::string, std::string> tmp;
				tmp[firstEl] = secondEl;
				
				//std::cout << "[debug]" << firstEl << " " << secondEl << "\n";
				itmp.close();
			}
		}
		else
		{
			insideObj = true;
		}
		/*else
		{
			if(!insideObj)
		}*/
		
		//std::cout << vector[i] << "\n===============\n";
		//ofile << vector[i] << "\n";
	}
    //ofile.close();
	file.close();
}