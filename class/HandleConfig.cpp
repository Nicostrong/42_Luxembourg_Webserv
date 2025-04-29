/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/29 13:56:19 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HandleConfig.hpp"
#include "../includes/lib.hpp"

HandleConfig::HandleConfig()
{
	
}

HandleConfig::HandleConfig(const char *filename)
{
	readConfigFile(filename);
	cleanMap();
}

HandleConfig::HandleConfig(HandleConfig& copy)
{
	this->webconfMap = copy.webconfMap;
}

HandleConfig& HandleConfig::operator=(HandleConfig& copy)
{
	if(this != &copy)
	{
		this->webconfMap = copy.webconfMap;
	}
	return *this;
}

HandleConfig::~HandleConfig()
{
	
}

bool handleCurlyBrackets(std::string line, int *countCurlyBrackets)
{
	if (line.find("{") != std::string::npos)
		(*countCurlyBrackets)++;
	if (line.find("}") != std::string::npos)
		(*countCurlyBrackets)--;
	if (*countCurlyBrackets < 0)
	{
		std::cout << "Error: More closing } that {./n";
		return (false);
	}
	return (true);
}

void HandleConfig::readConfigFile(const char *filename)
{
	std::vector<std::string> vector;
	std::ifstream file(filename);
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
		if (vector[i].find('{') != std::string::npos)
		{
			std::string key = vector[i];
			std::string concat = "";
			countCurlyBrackets++;
			i++;
			while(countCurlyBrackets > 0)
			{
				concat += vector[i];
				if(!handleCurlyBrackets(vector[i], &countCurlyBrackets))
					return ;
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
	std::stringstream ss(line);
	ss >> key;
	ss >> value;
	this->webconfMap[key] = value;
}

void HandleConfig::handleObjLine(std::string& first, std::string& second)
{
	std::stringstream ss(first);
	std::string key, part1, part2;
	ss >> part1;
	ss >> part2;
	key = part1 + " " + part2;
	this->webconfMap[key] = second;
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

std::map<std::string, std::string> HandleConfig::getwebconfMap()
{
	return this->webconfMap;
}

void HandleConfig::printwebconfMap()
{
	std::map<std::string, std::string>::iterator it = webconfMap.begin();
	while(it != webconfMap.end())
	{
		std::cout << "" << it->first << "\n" << it->second << "\n";
		it++;
	}
}