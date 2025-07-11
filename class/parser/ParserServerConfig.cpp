/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:15:01 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 13:36:38 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/ParserServerConfig.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Constructor ParserServerConfig with filename of config file in argument
 */
ParserServerConfig::ParserServerConfig( const std::string& filename )
		: _allTokens(NULL)
{
	try
	{
		std::string			content;
		Token*				head = NULL;

		checkExtension(filename);

		Ressource		file(filename);

		file.isFail() ? throw FileError() : content = file.getRaw();
		content.empty() ? throw EmptyConfigError() : formatString(content);
		head = Token::tokenize(this->_formatedString);
		this->_allTokens = head;
		if (!this->_allTokens)	
			throw EmptyConfigError();
		CheckerTokens::check(*this->_allTokens);
	}
	catch(const std::exception& e)
	{
		if (this->_allTokens)
			this->_allTokens->deleteList();
		throw ;
	}
	return ;
}

/*
 *	Destructor
 */
ParserServerConfig::~ParserServerConfig( void )
{
	return ;
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

// c++ -Wall -Werror -Wextra -std=c++98 ParserServerConfig.cpp ParserServerConfig_p.cpp ParserServerConfig_e.cpp -DPARSER=1 -o a


#ifdef PARSER

int main( void )
{
	try
	{
		ParserServerConfig		parser("../../config/webserver.conf");
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
#endif