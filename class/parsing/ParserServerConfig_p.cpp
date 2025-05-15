/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig_p.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 06:55:49 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 11:26:56 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ParserServerConfig.hpp"
#include "../../includes/Token.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

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
#ifdef DEBUG
	for (it = this->_serverToken.begin(); it != this->_serverToken.end(); it++)
	{
		std::cout << "PRINT TOKEN LIST" << std::endl;
		(*it)->printToken();
	}
#endif
	return ;
}

/*
 *	Transform the listen with ip and port in two different directives
 */
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
 *	Check the extension of the config file
 */
void		ParserServerConfig::checkExtension( const std::string& filename )
{
	if (filename.size() < 5 || filename.substr(filename.size() - 5) != ".conf")
		throw BadExtensionFile();
	return ;
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
		throw FileError();
	*pos = content.find(keyword, *pos);
	if (*pos == std::string::npos)
		throw FileError();
	*pos += keyword.length();
	while (*pos < content.size() && content[*pos] != (end_char - 2))
		++(*pos);
	if (*pos == content.size())
		throw FileError();
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
		throw FileError();
	block = content.substr(blockStart, *pos - blockStart);
	return (block);
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