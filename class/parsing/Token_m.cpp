/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:01:27 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:01:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Token.hpp"

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