/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:34 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/29 13:04:01 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleConfig.hpp"

//#include "../includes/HandleConfig.hpp"
#include "../../includes/lib.hpp"

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
        if (line.compare("") != 0)
        {
            this->config_vec.push_back(line);
        }
	}
	file.close();
}

bool handleCurlyBrackets(std::string line, int& countCurlyBrackets)
{
	if (line.find("{") != std::string::npos)
		countCurlyBrackets++;
	if (line.find("}") != std::string::npos)
		countCurlyBrackets--;
	if (countCurlyBrackets < 0)
	{
		std::cout << "Error: More closing } that {./n";
		return (false);	
	}
	return (true);
}

void HandleConfig::genTmpMap()
{
	int countCurlyBrackets = 0;
    std::size_t i = 1; // VITAL !!! Must be 1
    while(i < config_vec.size())
	{
		if (config_vec[i].find('{') != std::string::npos)
		{
			std::string key = config_vec[i];
			std::string concat = "";
			countCurlyBrackets++;
			++i;
			while(countCurlyBrackets > 0)
			{
				concat += config_vec[i];
                if (config_vec[i].find("{") != std::string::npos)
                {
                    countCurlyBrackets++;
                }
                if (config_vec[i].find("}") != std::string::npos)
                {
                    countCurlyBrackets--;
                }
                if (countCurlyBrackets < 0)
                {
                    std::cout << "Error: More closing } that {./n";
                }
				++i;
			}
			tmpMap[key] = concat;
		}
		else
		{
			tmpMap[config_vec[i]] = config_vec[i];
		}
        ++i;
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
    std::cout << "[debug] web\n";
	while(it != webconfMap.end())
	{
		std::cout << "\n==========\n" << it->first << "\n" << it->second << "\n==========\n";
		it++;
	}
}