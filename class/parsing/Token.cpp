/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:55:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 08:46:39 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Token.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Constructor Token
 */
Token::Token( Type type, const std::string& value )
				: _type(type), _value(value), _next(NULL)
{
	return ;
}

/*
 *	Destructor Token
 */
Token::~Token( void )
{
	delete this->_next;
	return ;
}

/*
 *	List of valid key for directives
 */
const std::string		directiveKeys[] = {
											"listen",
											"server_name",
											"root",
											"index",
											"max_connection_client",
											"client_max_body_size",
											"return",
											"autoindex"
										};

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

/*
 *	Parse a string and transform each wodr into a Token
 */
Token*		Token::tokenize( const std::string& input )
{
	std::istringstream		iss(input);
	std::string				word;
	Token*					head = NULL;
	Token*					current = NULL;
	int						braceCount = 0;
	bool					inServer = false;
	bool					inLocation = false;
	bool					inErrorBlk = false;
	bool					inHTTP = false;

	try
	{
		while (iss >> word)
		{
			if (word == "server")
			{
				Token*		serverTok = new Token(Token::SERVER, word);
				
				attachToken(head, current, serverTok);
				inServer = true;
			}
			if (word == "{" || word == "}")
				current = createBrace(word, head, current, braceCount, inLocation, inErrorBlk, inServer);
			if (word == "location")
				current = createLocation(iss, head, current, braceCount, inLocation);
			if (word == "error_page")
				current = createErrorPage(iss, word, head, current, braceCount, inErrorBlk);
			if (word == ";")
				current = createSemicolon(word, head, current, inHTTP);
			if (isDirectiveKey(word))
				current = createDirective(iss, word, head, current);
			if (!inServer && word != "server" && word != "}")
				throw Token::TokenError("Unexpected data outside server block");
			if (!isDirectiveKey(word))
				throw Token::TokenError("Unknown directive: " + word);
		}

		if (braceCount != 0)
			throw Token::TokenError("Mismatched braces: some '{' or '}' are not closed properly");
		if (inLocation || inErrorBlk || inHTTP || inServer)
			throw Token::TokenError("Unclosed block.");
	}
	catch ( const std::exception& e )
	{
		deleteChain(head);
		throw ;
	}
	return (head);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

// c++ -Wall -Werror -Wextra -std=c++98 Token.cpp Token_p.cpp Token_gs.cpp ParserServerConfig.cpp ParserServerConfig_p.cpp ParserServerConfig_e.cpp -DTOKEN=1 -o a

#ifdef TOKEN

int main( void )
{
	try
	{
		std::string		config = "{ listen 8080 ; server_name localhost ; \
									root ./www/html ; index index.html ; \
									max_connection_client 10 ; client_max_body_size 5M ; \
									error_page { 403 ./errors/403.html ; \
									404 ./errors/404.html ; 405 ./errors/405.html ; \
									409 ./errors/409.html ; 413 ./errors/413.html ; \
									418 ./errors/418.html ; 500 ./errors/500.html ; } \
									location / { autoindex off ; allow GET POST DELETE HEAD ; } \
									location /cgi-bin/ { root ./www/data; cgi { \
									.py /usr/bin/python3; .php /usr/bin/php-cgi; } } } ";
		
		Token*			tokens = Token::tokenize(config);
		
		std::cout << "Pointeur de HEAD: " << tokens << std::endl;
		tokens->printToken();
		
		delete tokens;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}

#endif