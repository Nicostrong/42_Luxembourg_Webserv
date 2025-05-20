/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:27 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/20 06:59:28 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"

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
			else if (word == "{" || word == "}")
				current = createBrace(word, head, current, braceCount, inLocation, inErrorBlk, inServer);
			else if (word == "location")
				current = createLocation(iss, head, current, braceCount, inLocation);
			else if (word == "error_page")
				current = createErrorPage(iss, word, head, current, braceCount, inErrorBlk);
			else if (word == ";")
				current = createSemicolon(word, head, current, inHTTP);
			else if (isDirectiveKey(word))
				current = createDirective(iss, word, head, current);
			else if (!inServer && word != "server" && word != "}")
				throw Token::TokenError("Unexpected data outside server block");
			else
				throw Token::TokenError("Unexpected data in server block");
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

/*
 *	Delete all Tokens on the linked list of tokens
 */
void		Token::deleteList( void )
{
	this->deleteChain(this);
	return ;
}