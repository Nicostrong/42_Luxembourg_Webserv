/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 13:16:45 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleConfig.hpp"
#include <vector>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

void HandleConfig::readConfigFile(const char *filename)
{
	std::vector<std::string> vector;
	std::ifstream file(filename);
	std::size_t found;
	int countCurlyBrackets;

	if (!file.is_open())
	{
        std::cerr << "Error opening file " << filename << std::endl;
        return ;
    }
	std::string line;
	while(getline(file, line))
	{
		vector.push_back(line);
		//std::cout << vector.back() << "\n===================\n";
	}
	countCurlyBrackets = 0;
	//std::map<std::string, std::string> tmpMap;
	for(int i = 1; i < vector.size(); i++)
	{
		//std::cout << vector[i] << "\n===================\n";
		found = vector[i].find('{');
		if (found != std::string::npos)
		{
			std::string key = vector[i];
			std::string concat = "";
			std::string tmp;
			countCurlyBrackets++;
			i++;
			while(countCurlyBrackets > 0)
			{
				concat += vector[i];
				//std::cout << "[debug} concat" << vector[i] << "\n===================\n";
				found = vector[i].find("{");
				if (found != std::string::npos)
					countCurlyBrackets++;
				found = vector[i].find("}");
				if (found != std::string::npos)
					countCurlyBrackets--;
				if (countCurlyBrackets < 0)
				{
					std::cout << "Error: More closing } that {./n";
					return ;	
				}
				i++;
			}
			tmpMap[key] = concat;
			//std::cout << "" << key << " " << tmpMap[key] << "\n===================\n";
		}
		else
		{
			tmpMap[vector[i]] = vector[i];
			//std::cout << "" << vector[i] << " " << tmpMap[vector[i]] << "\n===================\n";
		}	
	}
	file.close();
}

void HandleConfig::handleSimpleLine(std::string& line)
{
	//std::cout << "[debug simple line]." << line << "." << "\n";
	std::string key, value;
	key = line;
	std::size_t start = key.find_first_not_of(" \t");
	key.erase(0, start);
	std::size_t end1 = key.find("\t");
	std::size_t end2 = key.find(" ");
	std::size_t end;
	if (end1 == std::string::npos && end2 == std::string::npos)
	{
		std::cout << "Error: End of Word not found.\n";
		return;
	}
	if (end1 != std::string::npos)
		end = end1;
	if (end2 != std::string::npos)
		end = end2;
	key.erase(end, key.size());
	//std::cout << "." << key << "." << "\n";
	
	// =============================================

	value = line;
	end = value.find_last_not_of(" \t");
	value.erase(end, value.size());
	start = value.find_last_of(" \t");
	value.erase(0, start);
	start = value.find_first_not_of(" \t");
	value.erase(0, start);
	//std::cout << "." << value << "." << "\n";
	
	this->nicoMap[key] = value;
}

void HandleConfig::handleObjLine(std::string& first, std::string& second)
{
	//std::cout << "[debug obj first]" << first << "\n";
	//std::cout << "[debug obj second]" << second << "\n";
	std::string key = first;
	key.erase(0, key.find_first_not_of(" \t"));
	key.erase(key.find_first_of("{"), key.size());
	key.erase(key.find_last_not_of(" /t")+1, key.size());
	//std::cout << "[debug key]" << "." << key << "." << "\n";
	
	std::string value = second;
	//value.erase(value.find_first_of("{"), value.size());
	//std::cout << "[debug value]" << "." << value << "." << "\n";
	this->nicoMap[key] = value;
}

void HandleConfig::cleanMap()
{
	
	std::map<std::string, std::string>::iterator it = tmpMap.begin();
	it++;
	while(it != tmpMap.end())
	{
		std::string first = static_cast<std::string>(it->first);
		std::string second = static_cast<std::string>(it->second);
		if(it->first.find("{") != std::string::npos)
		{
			handleObjLine(first, second);
		}
		else
		{
			handleSimpleLine(first);
		}
		it++;
	}
	
	// =======================================
	
	it = nicoMap.begin();
	while(it != nicoMap.end())
	{
		std::cout << "" << it->first << "\n" << it->second << "\n";
		it++;
	}	
}