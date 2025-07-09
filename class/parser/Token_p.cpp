/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_p.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:35:46 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/09 08:29:31 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"
#include "../../includes/http/HttpBase.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Link the new token to the chain
 */
void		Token::attachToken( Token*& head, Token*& current, Token* newToken )
{
	if (!head)
		head = newToken;
	else
		current->_next = newToken;
	current = newToken;
	return ;
}

/*
 *	Delete the chain of tokens
 */
void		Token::deleteChain( Token* head )
{
	while (head)
	{
		Token*		tmp = head;

		head = head->_next;
		tmp->_next = NULL;
		delete tmp;
	}
	return ;
}

/*
 *	Check if the key is a valid key
 */
bool		Token::isDirectiveKey( const std::string& word )
{
	for (size_t i = 0; i < sizeof(directiveKeys) / sizeof(*directiveKeys); ++i)
		if (word == directiveKeys[i])
			return (true);
	return (false);
}

/*
 *	Create an Error Token
 */
Token*		Token::createErrorPage(	std::istringstream& iss,
									std::string word,
									Token*& head,
									Token*& current,
									int& braceCount,
									bool& inErrorBlk )
{
	Token*			errorStart = new Token(Token::ERROR_PAGE, word);
	std::string		next;
	std::string		code;
	std::string		path;
	std::string		semi;

	attachToken(head, current, errorStart);
	if (!(iss >> next) || next != "{")
		throw Token::TokenError("Expected '{' after error_page");
	braceCount++;

	Token*			errBraceStart = new Token(Token::ERR_BLK_S, "{");

	attachToken(head, current, errBraceStart);
	inErrorBlk = true;
	while (iss >> code && code != "}")
	{
		if (!(iss >> path))
			throw Token::TokenError("Missing path after error code '" + code + "'");
		if (!(iss >> semi) || semi != ";")
			throw Token::TokenError("Missing ';' after error_page value");
		attachToken(head, current, new Token(Token::DIR_K, code));
		attachToken(head, current, new Token(Token::DIR_V, path));
		attachToken(head, current, new Token(Token::SEMICOLON, ";"));
	}
	if (code != "}")
		throw Token::TokenError("Missing closing '}' after error_page block");

	Token*			errBraceEnd = new Token(Token::ERR_BLK_E, code);

	attachToken(head, current, errBraceEnd);
	inErrorBlk = false;
	braceCount--;
	return (current);
}

/*
 *	Gestion des braces { et }
 */
Token*		Token::createBrace(	const std::string& word, Token*& head,
								Token*& current, int& braceCount,
								bool& inLocation, bool& inErrorBlk,
								bool& inServer )
{
	Token*		blk = new Token(word == "{" ? Token::SER_BLK_S : Token::SER_BLK_E, word);

	attachToken(head, current, blk);
	if (word == "{")
	{
		braceCount++;
		if (inServer)
			return (current);
		!inErrorBlk ? inErrorBlk = true : 
		!inLocation ? inLocation = true : 
		throw Token::TokenError("Unexpected '{' inside a block");
	}
	else 
	{
		braceCount--;
		inLocation ? inLocation = false :
		inErrorBlk ? inErrorBlk = false :
		inServer ? inServer = false :
		throw Token::TokenError("Unexpected '}' inside a block");
	}
	return (current);
}

/*
 *	Gestion du semicolon
 */
Token*		Token::createSemicolon(	const std::string& word, Token*& head,
									Token*& current, bool& inHTTP )
{
	Token*		semi = new Token(Token::SEMICOLON, word);

	attachToken(head, current, semi);
	inHTTP = false;
	return (current);
}

/*
 *	Gestion des directives
 */
Token*		Token::createDirective(	std::istringstream& iss,
									const std::string& word,
									Token*& head, Token*& current )
{
	Token*		dirKey = new Token(Token::DIR_K, word);

	attachToken(head, current, dirKey);

	std::string		value;

	if (!(iss >> value) || value == ";")
		throw Token::TokenError("Missing value after directive '" + word + "'");

	while (!value.empty() && value != ";")
	{
		Token*		dirVal = new Token(Token::DIR_V, value);

		attachToken(head, current, dirVal);
		if (!(iss >> value))
			throw Token::TokenError("Unexpected end of input while parsing directive '" + word + "'");
	}
	if (value != ";")
		throw Token::TokenError("Expected ';' after directive value for '" + word + "'");

	Token*		semi = new Token(Token::SEMICOLON, ";");

	attachToken(head, current, semi);
	return (current);
}

/*
 *	Create a Location Token
 */
Token*		Token::createLocation(	std::istringstream& iss, Token*& head, 
									Token*& current, int& braceCount,
									bool& inLocation )
{
	std::string		path;
	std::string		brace;
	std::string		token;

	if (!(iss >> path))
		throw Token::TokenError("Expected path after 'location'");

	path = HttpBase::normalizeUri(path);
	
	Token*		locKey = new Token(Token::LOCATION, path);

	attachToken(head, current, locKey);
	if (!(iss >> brace) || brace != "{")
		throw Token::TokenError("Expected '{' after location path");
	braceCount++;

	Token*		locStart = new Token(Token::LOC_BLK_S, "{");

	attachToken(head, current, locStart);
	inLocation = true;
	while (iss >> token && token != "}")
	{
		if (token == "allow")
		{
			std::string		method;

			attachToken(head, current, new Token(Token::HTTP_K, token));
			while (iss >> method && method != ";")
				attachToken(head, current, new Token(Token::HTTP_V, method));
			if (method != ";")
				throw Token::TokenError("Missing ';' after allow");
			attachToken(head, current, new Token(Token::SEMICOLON, ";"));
		}
		else if (isDirectiveKey(token))
			createDirective(iss, token, head, current);
		else if (token == "cgi")
			createCGIDirective(iss, token, head, current);
		else
			throw Token::TokenError("Unknown directive inside location block: " + token);
	}
	if (token != "}")
		throw Token::TokenError("Missing closing '}' after location block");

	Token*		locEnd = new Token(Token::LOC_BLK_E, "}");

	attachToken(head, current, locEnd);
	inLocation = false;
	braceCount--;
	return (current);
}

/*
 *	Gestion des CGIdirectives
 */
Token*		Token::createCGIDirective(	std::istringstream& iss,
										const std::string& word,
										Token*& head, Token*& current )
{
	std::string		key;
	std::string		value;
	Token*			cgi = new Token(Token::CGI, word);

	attachToken(head, current, cgi);
	if (!(iss >> value) || value != "{")
		throw Token::TokenError("Expected '{' for cgi block");

	Token*		brace = new Token(Token::CGI_BLK_S, value);

	attachToken(head, current, brace);
	while (iss >> key && key != "}")
	{
		Token*		cgiKey = new Token(Token::CGI_K, key);

		attachToken(head, current, cgiKey);
		if (!(iss >> value) || value == ";")
			throw Token::TokenError("Missing value after cgi key '" + key + "'");
		
		Token*		cgiVal = new Token(Token::CGI_V, value);

		attachToken(head, current, cgiVal);
		iss >> value;
		if (value != ";")
			throw Token::TokenError("Expected ';' after cgi value for key '" + key + "'");

		Token*		semi = new Token(Token::SEMICOLON, ";");

		attachToken(head, current, semi);
	}
	if (key != "}")
		throw Token::TokenError("Missing closing '}' after cgi block");

	Token*		braceEnd = new Token(Token::CGI_BLK_E, key);
	
	attachToken(head, current, braceEnd);
	return (current);
}