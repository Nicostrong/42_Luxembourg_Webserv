/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:15:01 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:27 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ParserServerConfig.hpp"
#include "../includes/Token.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	le Parser recoit un path d un fichier de config
 *	il la passe a Ressource qui l ouvre et le lit
 *	Parser verifie les erreur et recupere le contenu du fichier
 *	il format le contenue en supprimant les comments, les tab et les \n
 *	il ajoute un espace devant chaque ';' et '{'
 *	il tokenize la string qui sera check par la class Token
 *	il split les token en plusieurs token de server
 *	il cree les server avec les tokens
 */
ParserServerConfig::ParserServerConfig( const std::string& filename ) : _allTokens(NULL)
{
	try
	{
		std::string			content;
		Token*				head = NULL;

		checkHiddenFile(filename);

		Ressource		file(filename);

		file.isFail() ? throw FileError() : content = file.getRaw();
		content.empty() ? throw EmptyConfigError() : formatString(content);
		head = Token::tokenize(this->_formatedString);
		head->printToken();
		this->_allTokens = head;
		if (!this->_allTokens)	
			throw EmptyConfigError();
		CheckerTokens::check(this->_allTokens);
		splitServerToken(this->_allTokens);
		if (this->_serverToken.empty())
			throw ParsingError("Server list empty");
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
	std::list<Token*>::iterator		it;

	for (it = this->_serverToken.begin(); it != this->_serverToken.end(); it++)
		delete (*it);
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
void		ParserServerConfig::formatString( const std::string& content )
{
	std::string		block;
		
	block = content;
	block = stripComments(block);
	block = removeWhitespace(block);
	insertChar(block, ';', ' ');
	insertChar(block, '{', ' ');
	insertChar(block, '}', ' ');
	formatHost(block);
	this->_formatedString = block;
	return ;
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
 *	Remove all spaces and put just one space betwenn each word
 */
std::string		ParserServerConfig::removeWhitespace(const std::string& input)
{
	std::string		output;

	for (size_t i = 0; i < input.length(); ++i)
	{
		if (std::isspace(input[i]))
		{
			if (!output.empty() && output[output.length() - 1] != ' ')
				output += ' ';
		}
		else
			output += input[i];
	}
	return (output);
}


/*
 *	Add a space before a semicolon
 */
void			ParserServerConfig::insertChar( std::string &str, char target, char toInsert )
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] == target)
		{
			str.insert(i, 1, toInsert);
			++i;
		}
	}
	return ;
}

void	ParserServerConfig::formatHost( std::string& input )
{
	std::istringstream		iss(input);
	std::ostringstream		oss;
	std::string				word;

	while (iss >> word)
	{
		size_t		pos = word.find(':');

		if (pos != std::string::npos)
		{
			std::string		left = word.substr(0, pos);
			std::string		right = word.substr(pos + 1);
			oss << right << " host " << left << " ";
		}
		else
			oss << word << " ";
	}
	input = oss.str();
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
	return (block);
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

/*
 *	Split the Tokens list to separate each server config
 */
void			ParserServerConfig::splitServerToken( Token *head )
{
	while (head)
	{
		if (head->getType() == Token::SERVER)
		{
			Token*		server = head;
			Token*		tmp = head;

			while (tmp && tmp->getType() != Token::SER_BLK_E)
				tmp = tmp->getNext();
			if (tmp)
			{
				head = tmp->getNext();
				tmp->setNextToNull();
				this->_serverToken.push_back(server);
			}
			else
				break;
		}
		else
			head = head->getNext();
	}
	std::list<Token*>::iterator		it;

	for (it = this->_serverToken.begin(); it != this->_serverToken.end(); it++)
	{
		std::cout << "PRINT TOKEN LIST" << std::endl;
		(*it)->printToken();
	}
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Get the tokens list of the config file
 */
const std::list<Token*>&	ParserServerConfig::getListTokens( void ) const { return (this->_serverToken); }

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

#ifdef TESTMAIN

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