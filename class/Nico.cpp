/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:15:01 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/29 21:11:21 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Nico.hpp"

ParserServerConfig::ParserServerConfig( const std::string &filename )
{
	try
	{
		parseConfigFile(filename);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	LOG_DEB("ParserServerConfig constructor called.");
	return ;
}

ParserServerConfig::~ParserServerConfig( void )
{
	LOG_DEB("Destructor of ParserServerConfig called.");
	return ;
}

void		ParserServerConfig::parseConfigFile( const std::string &filename )
{
	std::ifstream		file(filename.c_str());
	std::string			line;
	std::string			content;
	size_t				pos = 0;

	if (!file.is_open())
		throw std::runtime_error("Unable to open config file: " + filename);

	while (std::getline(file, line))
		content += stripComments(line) + "\n";
	file.close();

	while ((pos = content.find("server", pos)) != std::string::npos)
	{
		size_t			blockStart = content.find("{", pos);
		size_t			i;
		int				braceCount = 1;
		std::string		block;

		if (blockStart == std::string::npos)
			break;
		i = blockStart + 1;
		while (i < content.size() && braceCount > 0)
		{
			if (content[i] == '{')
				braceCount++;
			else if (content[i] == '}')
				braceCount--;
			i++;
		}
		if (braceCount != 0)
			throw std::runtime_error("Unmatched braces in server block");

		block = content.substr(blockStart + 1, i - blockStart - 2);
		parseServerBlock(block);
		pos = i;
	}
	return ;
}

void			ParserServerConfig::parseServerBlock( const std::string &block )
{
	std::istringstream					iss(block);
	std::string							line;
	std::map<std::string, std::string>	config;
	int									port = -1;

	while (std::getline(iss, line))
	{
		size_t				delim;
		std::string			key;
		std::string			value;

		line = trim(line);
		if (line.empty())
			continue ;
		
		if (line.find("location") == 0)
		{
			std::string		locationKey;
			std::string		locationBlock;

			locationKey = line.substr(0, line.find("{"));
			locationKey = trim(locationKey);
			locationBlock = extractBlock(iss);
			config[locationKey] = locationBlock;
			continue ;
		}

		if (line.find("error_page") == 0 && line.find("{") != std::string::npos)
		{
			std::string		errorBlock;
			
			errorBlock = extractBlock(iss);
			config["error_page"] = errorBlock;
			continue ;
		}

		if (line[line.length() - 1] != ';')
			throw std::runtime_error("Syntax error: missing ';' in line: " + line);

		delim = line.find_first_of(" \t");
		key = line.substr(0, delim);
		value = line.substr(delim + 1);

		if (!value.empty() && value[value.length() - 1] == ';')
			value = value.substr(0, value.length() - 1);

		key = trim(key);
		value = trim(value);

		if (key == "listen")
			port = parsePort(value);

		config[key] = value;
	}

	if (port == -1)
		throw std::runtime_error("Missing 'listen' directive in server block");

	this->_servers[port] = config;
	return ;
}

size_t			ParserServerConfig::countChar( const std::string &str, char c )
{
	size_t		count;
	
	count = 0;
	for (size_t i = 0; i < str.length(); ++i)
		if (str[i] == c) ++count;
	return (count);
}

std::string		ParserServerConfig::trim( const std::string &s )
{
	size_t		start;
	size_t		end;

	start = s.find_first_not_of(" \t\n\r");
	end = s.find_last_not_of(" \t\n\r");
	if (start == std::string::npos || end == std::string::npos)
		return ("");
	return (s.substr(start, end - start + 1));
}

std::string		ParserServerConfig::extractBlock( std::istringstream &iss )
{
	std::string		block;
	std::string		line;
	int				braceCount = 1;

	while (std::getline(iss, line) && braceCount != 0)
	{
		size_t		open;
		size_t		close;
		open = countChar(line, '{');
		close = countChar(line, '}');
		braceCount += open - close;
		block += line + "\n";
	}
	if (braceCount != 0)
		throw std::runtime_error("Unmatched braces in block");
	return (block);
}

/*
 *	Remove comment of the line
 */
std::string		ParserServerConfig::stripComments( const std::string &line )
{
	size_t		pos;
	
	pos = line.find("#");
    if (pos != std::string::npos)
        return line.substr(0, pos);
    return (line);
}

int				ParserServerConfig::parsePort( const std::string &value )
{
	size_t		colonPos;
	
	colonPos = value.find(":");
	if (colonPos != std::string::npos)
		return std::atoi(value.substr(colonPos + 1).c_str());
	return (std::atoi(value.c_str()));
}

void			ParserServerConfig::printServers( void ) const
{
	std::map<int, std::map<std::string, std::string> >::const_iterator		it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
	{
		std::map<std::string, std::string>::const_iterator		sub;

		std::cout << "\n[SERVER ON PORT " << it->first << "]\n";

		for (sub = it->second.begin(); sub != it->second.end(); ++sub)
			std::cout << sub->first << " : " << sub->second << "\n";
	}
}

#ifdef TEST

int main( void )
{
	try
	{
		ParserServerConfig		parser("../config/webserver.conf");
		parser.printServers();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
// c++ -Wall -Werror -Wextra -std=c++98 Nico.cpp -DTEST=1 -o a
#endif