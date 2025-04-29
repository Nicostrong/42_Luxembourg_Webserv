/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/29 15:33:46 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HandleConfig.hpp"
#include "../includes/lib.hpp"

HandleConfig::HandleConfig()
{
	return ;
}

HandleConfig::~HandleConfig()
{
	return ;
}

HandleConfig::HandleConfig(const char *filename)
{
	configfilename = filename;
}

HandleConfig::HandleConfig(const HandleConfig& copy)
{
	this->webconfMap = copy.webconfMap;
}

HandleConfig& HandleConfig::operator=(const HandleConfig& copy)
{
	if(this != &copy)
	{
		this->webconfMap = copy.webconfMap;
	}
	return *this;
}

void HandleConfig::saveRawConfig(const char *filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
        std::cerr << "Error opening file " << filename << std::endl;
        return ;
    }
	std::string line;
	while(getline(file, line))
	{
		config_vec.push_back(line);
	}
	file.close();
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

void HandleConfig::genTmpMap()
{
	int countCurlyBrackets = 0;
	std::vector<std::string>::iterator it;
	for(it = config_vec.begin(); it != config_vec.end(); ++it)
	{
		if (it->find('{') != std::string::npos)
		{
			std::string key = *it;
			std::string concat = "";
			countCurlyBrackets++;
			it++;
			while(countCurlyBrackets > 0)
			{
				concat += *it;
				if(!handleCurlyBrackets(*it, &countCurlyBrackets))
					return ;
				it++;
			}
			tmpMap[key] = concat;
		}
		else
		{
			tmpMap[*it] = *it;
		}	
	}
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

void HandleConfig::genWebconfMap()
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