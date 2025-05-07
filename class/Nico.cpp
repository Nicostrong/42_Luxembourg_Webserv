/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:15:01 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/07 11:46:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Nico.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	The parser call ressoource and receive a string with all the file inside
 *	it check if an error or the file is empty
 *	start the parsing
 *	first it split each block of server on list of server block without comments
 *	each block of server are parsing to a map of string keyWord/string value
 *	at the end the attribut _servers containt a map of server (port/config)
 *	for each port we can creat a server object with specific config
 */
ParserServerConfig::ParserServerConfig( std::string filename )
{
	try
	{
		std::string		content;

		checkHiddenFile(filename);

		Ressource		file(filename);

		file.isFail() ? throw FileError() : content = file.getRaw();
		content.empty() ? throw EmptyConfigError() : parseConfigFile(content);
		if (this->_servers.empty())	
			throw EmptyConfigError();
		LOG_DEB("ParserServerConfig constructor called.");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	Destructor
 */
ParserServerConfig::~ParserServerConfig( void )
{
	LOG_DEB("Destructor of ParserServerConfig called.");
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Check if the filename isn't an hidden file
 */
void		ParserServerConfig::checkHiddenFile( const std::string& filename )
{
	size_t		posSlash = filename.find("/.");

	if (posSlash != std::string::npos)
		throw HiddenFile();
	if (filename.size() < 5 || filename.substr(filename.size() - 5) != ".conf")
		throw BadExtensionFile();
	return ;
}

/*
 *	The parser of the config file split all server block and remove all comments
 *	and save each server block on a list.
 *	Each server blok are transformed on map of key/value
 */
void		ParserServerConfig::parseConfigFile( const std::string& content )
{
	int								index = -1;
	size_t							pos = 0;
	std::list<std::string>			servers;
	std::list<std::string>::iterator	it;

	//	we extract all block server and save the block on a list of string
	while ((pos = content.find("server", pos)) != std::string::npos)
		servers.push_back(stripComments(extractBlock(content, "server", '}', &pos)));
	if (servers.size() < 1)
		throw ParsingError("ExtractBlock server.");
	//	we transform each server block on map of key/value
	for (it = servers.begin(); it != servers.end(); it++)
		parseServerBlock(*it);
	return ;
}

/*
 *	This method extract a block of data from the keyword to the ending char
 */
std::string		ParserServerConfig::extractBlock(	const std::string& content,
													const std::string& keyword,
													char end_char, size_t* pos)
{
	size_t		blockStart;
	int			openBraces;
	std::string	block;

	if (!pos || *pos >= content.size())
		throw ParsingError("Bad position cursor");
	*pos = content.find(keyword, *pos);
	if (*pos == std::string::npos)
		throw ParsingError("Start keyword not found.");
	*pos += keyword.length();
	while (*pos < content.size() && content[*pos] != (end_char - 2))
		++(*pos);
	if (*pos == content.size())
		throw BraceError();
	blockStart = *pos;
	openBraces = 1;
	++(*pos);
	while (*pos < content.size() && openBraces > 0)
	{
		if (content[*pos] == (end_char - 2))
			openBraces++;
		else if (content[*pos] == end_char)
			openBraces--;
		++(*pos);
	}
	if (openBraces != 0)
		throw BraceError();
	block = content.substr(blockStart, *pos - blockStart);
#ifdef DEBUG
	std::cout << "BLOCK " << keyword << " TEST" << std::endl;
	std::cout << block << std::endl;
#endif
	return (block);
}


void		ParserServerConfig::parseServerBlock( const std::string& serverBlock )
{
	int									index = -1;
	std::istringstream					iss(serverBlock);
	std::string							token;
	std::string							key;
	std::map<std::string, std::string>	config;
	std::vector<std::string>			tokens;
	bool								readingDirective = false;

	while (iss >> token)
	{
		if (token == "{" || token == "}")
			if (!readingDirective) continue;
		else if (!readingDirective)
		{
			key = token;
			tokens.clear();
			readingDirective = true;
		}
		else if (token == ";")
		{
			std::string		value;

			for (size_t i = 0; i < tokens.size(); i++)
			{
				if (i) value += " ";
				value += tokens[i];
			}
			config[key] = value;
			readingDirective = false;
		}
		else if (token == "{")
		{
			std::string		blockValue = "{";
			int				braceLevel = 1;
			std::string		innerToken;

			while (braceLevel > 0 && iss >> innerToken)
			{
				if (innerToken == "{") braceLevel++;
				else if (innerToken == "}") braceLevel--;
				blockValue += " " + innerToken;
			}
			config[key] = blockValue;
			readingDirective = false;
		}
		else
		{
			tokens.push_back(token);
		}
	}
	this->_servers[index++] = config;
}

/*
 *	remove all spaces at de start and the end of the line
 */
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

/*
 *	check if the line need a semicolon at the end
 */
bool			ParserServerConfig::requireSemicolon( const std::string& line )
{
#ifdef DEBUG
	std::cout << "LINE ON REQUIRE SSMICOLON:" << std::endl;
	std::cout << line <<std::endl;
#endif
	if (line.find("error_page") == 0 || line.find("location") == 0 || line.find("limit_except") == 0)
		return  (false);
	if (!line.empty() && line.find('{') == std::string::npos && \
		line.find('}') == std::string::npos)
	{
		size_t		lastChar;
		
		lastChar = line.find_last_not_of(" \t");
		if (lastChar != std::string::npos && line[lastChar] != ';')
			return (true);
	}
	return (false);
}

/*
 *	Remove all comments of the block
 */
std::string		ParserServerConfig::stripComments( const std::string &block )
{
	std::string			ret;
	std::string			line;
	std::istringstream	iss(block);
	
	while (std::getline(iss, line))
	{
		size_t		pos;

		pos = line.find("#");
		if (pos != std::string::npos)
			line = line.substr(0, pos);
		ret += line + "\n";
	}
	return (ret);
}

/*
 *	Catch the value of port and check if it's valid value
 */
int				ParserServerConfig::parsePort( const std::string &value )
{
	size_t		colonPos;
	int			port;
	
	colonPos = value.find(":");
	if (colonPos != std::string::npos)
		port = std::atoi(value.substr(colonPos + 1).c_str());
	else
		port = std::atoi(value.c_str());
	if (port <= 0 || port > 65535)
		throw PortValueException();
	return (port);
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Get just one map of one server
 */
const std::map<std::string, std::string>&		ParserServerConfig::getServer( size_t index ) const
{
	std::map<int, std::map<std::string, std::string> >::const_iterator		it;

	if (index >= this->_servers.size()) 
		throw GetServerMapError();
	it = this->_servers.begin();
	std::advance(it, index);
	return (it->second);
}

size_t		ParserServerConfig::getNumberServer( void ) const
{
	return (this->_servers.size());
}

/*******************************************************************************
 *								PRINTER										   *
 ******************************************************************************/

/*
 *	Print all servers of the config file
 */
void		ParserServerConfig::printServers( void ) const
{
	std::map<int, std::map<std::string, std::string> >::const_iterator		it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
	{
		std::map<std::string, std::string>::const_iterator					sub;

		std::cout << std::endl << "[SERVER ON PORT " << it->first << "]" << std::endl;
		for (sub = it->second.begin(); sub != it->second.end(); ++sub)
			std::cout << sub->first << " : " << sub->second << std::endl;
		std::cout << "--------------------------------------------------------------------------------" << std::endl;
	}
	return ;
}


void		ParserServerConfig::printOneServer( size_t index ) const
{
	std::map<int, std::map<std::string, std::string> >::const_iterator	it;
	std::map<std::string, std::string>::const_iterator					sub;
	
	if (index >= this->_servers.size()) 
	{
		std::cout << "[ERROR] No server found at index: " << index << std::endl;
		return ;
	}
	it = this->_servers.begin();
	std::advance(it, index);
	std::cout << std::endl << "[SERVER ON PORT " << it->first << "]" << std::endl;
	for (sub = it->second.begin(); sub != it->second.end(); ++sub)
		std::cout << sub->first << " : " << sub->second << std::endl;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsing error with data
 */
ParserServerConfig::ParsingError::ParsingError( const std::string &data ) throw()
{
	this->_msg = RED"[ERROR] Parsing data missed ';': " + data + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
ParserServerConfig::ParsingError::~ParsingError( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char		*ParserServerConfig::ParsingError::what() const throw()
{
	return (this->_msg.c_str());
}

/*
 *	Error while opening file config
 */
const char		*ParserServerConfig::FileError::what() const throw()
{
	return (RED "[ERROR] Opening file server config fail" RESET);
}

/*
 *	Error hidden file config
 */
const char		*ParserServerConfig::HiddenFile::what() const throw()
{
	return (RED "[ERROR] hidden file not config valid file" RESET);
}

/*
 *	Error bad extension file
 */
const char		*ParserServerConfig::BadExtensionFile::what() const throw()
{
	return (RED "[ERROR] Bad extension file." RESET);
}

/*
 *	Error empty file config
 */
const char		*ParserServerConfig::EmptyConfigError::what() const throw()
{
	return (RED "[ERROR] Empty file config or not valid." RESET);
}

/*
 *	Error brace number not correct
 */
const char		*ParserServerConfig::BraceError::what() const throw()
{
	return (RED "[ERROR] Brace open|close error." RESET);
}

/*
 *	Error while getting the server map
 */
const char		*ParserServerConfig::GetServerMapError::what() const throw()
{
	return (RED "[ERROR] Index out of range in getServer" RESET);
}

/*
 *	Port value exception
 */
const char		*ParserServerConfig::PortValueException::what() const throw()
{
	return (RED "[ERROR] Value of port not correct !" RESET);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef TEST

int main( void )
{
	try
	{
		ParserServerConfig		parser("../config/webserver.conf");
		parser.printServers();
		std::cout << "Number of server detected: " << parser.getNumberServer() << std::endl;
		std::cout << "Show of eatch server one by one." << std::endl;
		for (size_t i = 0; i < parser.getNumberServer(); i++)
			parser.printOneServer(i);
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