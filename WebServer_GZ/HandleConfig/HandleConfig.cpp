/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/24 15:59:05 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleConfig.hpp"
#include <vector>
#include <string>

HandleConfig::HandleConfig()
{
	
}

HandleConfig::HandleConfig(const char *filename)
{
	readConfigFile(filename);
	cleanMap();
	printNicoMap();
}

HandleConfig::HandleConfig(HandleConfig& copy)
{
	this->nicoMap = copy.nicoMap;
}

HandleConfig& HandleConfig::operator=(HandleConfig& copy)
{
	if(this != &copy)
	{
		this->nicoMap = copy.nicoMap;
	}
	return *this;
}

HandleConfig::~HandleConfig()
{
	
}

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
	}
	countCurlyBrackets = 0;
	for(size_t i = 1; i < vector.size(); i++)
	{
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
		}
		else
		{
			tmpMap[vector[i]] = vector[i];
		}	
	}
	file.close();
}

void HandleConfig::handleSimpleLine(std::string& line)
{
	std::string key, value;
	key = line;
	std::size_t start = key.find_first_not_of(" \t");
	key.erase(0, start);
	std::size_t end = key.find_first_of(" \t");
	if (end != std::string::npos)
	{
		key.erase(end, key.size());
	}
	else
	{
		std::cout << "Error: End of Word not found.\n";	
	}
	// =============================================

	value = line;
	end = value.find_last_not_of(" \t");
	value.erase(end, value.size());
	start = value.find_last_of(" \t");
	value.erase(0, start);
	start = value.find_first_not_of(" \t");
	value.erase(0, start);
	
	this->nicoMap[key] = value;
}

void HandleConfig::handleObjLine(std::string& first, std::string& second)
{
	std::string key = first;
	key.erase(0, key.find_first_not_of(" \t"));
	key.erase(key.find_first_of("{"), key.size());
	key.erase(key.find_last_not_of(" /t")+1, key.size());
	this->nicoMap[key] = second;
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
	this->tmpMap.clear();
}

std::map<std::string, std::string> HandleConfig::getNicoMap()
{
	return this->nicoMap;
}

void HandleConfig::printNicoMap()
{
	std::map<std::string, std::string>::iterator it = nicoMap.begin();
	while(it != nicoMap.end())
	{
		std::cout << "" << it->first << "\n" << it->second << "\n";
		it++;
	}
}
