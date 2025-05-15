/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_p.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:26:39 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 18:23:02 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CheckerTokens.hpp"

/*******************************************************************************
 *							Private Method									   *
 ******************************************************************************/

/*
 *	Call all the check function
 */
void		CheckerTokens::validate( void )
{
	checkBracesAndBlocks();
	checkHTTPKeyValuePairs();
	checkDirectiveKeyValuePairs();
	checkSemicolonAfterDirectiveValue();
	checkSemicolonAfterHTTPValue();
	checkSemicolonBeforeBlockEnd();
	checkDuplicatedKeysInScope();
	checkpath();
	checkBlockError();
	checkValue();
	checkCGI();
	checkMethodHTTP();
	assertFinalState();
	return ;
}

/*
 *	Check the number of brace and the localisation of block
 */
void		CheckerTokens::checkBracesAndBlocks( void )
{
	Token*		current = this->_head;

	while (current)
	{
		checkServerTokens(current);
		checkLocationTokens(current);
		checkErrorPageTokens(current);
		checkCGITokens(current);
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the brace and the localisation of block SERVER
 */
void		CheckerTokens::checkServerTokens( Token* current )
{
	if (current->getType() == Token::SERVER)
	{
		if (this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Server block not allowed in this scope");
	}
	else if (current->getType() == Token::SER_BLK_S)
	{
		if (this->_inServer || this->_inLocation || this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Server block not allowed in this scope");
		this->_inServer = true;
		++this->_braceCount;
	}
	else if (current->getType() == Token::SER_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount != 0 || this->_inLocation || this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inServer)
			this->_inServer = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
	return ;
}

/*
 *	Check the brace and the localisation of block ERROR_PAGE
 */
void		CheckerTokens::checkErrorPageTokens( Token* current )
{
	if (current->getType() == Token::ERROR_PAGE)
	{
		if (!this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Nested error block not allowed");
	}
	else if (current->getType() == Token::ERR_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("Error_page block not allowed outside server");
		if (this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Error_page block not allowed in this scope");
		this->_inErrorBlk = true;
	}
	else if (current->getType() == Token::ERR_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces ERROR " + current->getValue());
		if (!this->_inServer || this->_inLocation || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inErrorBlk)
			this->_inErrorBlk = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check the brace and the localisation of block LOCATION
 */
void		CheckerTokens::checkLocationTokens( Token* current )
{
	if (current->getType() == Token::LOCATION)
	{
		if (!this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Location block not allowed in this scope");
	}
	else if (current->getType() == Token::LOC_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("Location block not allowed outside server");
		if (this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Location block not allowed in this scope");
		this->_inLocation = true;
	}
	else if (current->getType() == Token::LOC_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces LOCATION " + current->getValue());
		if (this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inLocation)
			this->_inLocation = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check the brace and the localisation of block CGI
 */
void CheckerTokens::checkCGITokens( Token* current )
{
	if (current->getType() == Token::CGI)
	{
		if (!this->_inServer)
			throw CheckerError("CGI block not allowed outside server");
		if (this->_inErrorBlk || !this->_inLocation )
			throw CheckerError("CGI block not allowed in this scope");
	}
	else if (current->getType() == Token::CGI_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("CGI block not allowed outside server");
		if (!this->_inLocation)
			throw CheckerError("CGI block outside location");
		if (this->_inErrorBlk)
			throw CheckerError("CGI block not allowed in error block");
		this->_inCGI = true;
	}
	else if (current->getType() == Token::CGI_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces CGI " + current->getValue());
		if (!this->_inServer || this->_inErrorBlk || !this->_inLocation)
			throw CheckerError("Unexpected closing brace");
		if (this->_inCGI)
			this->_inCGI = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check if a HTTP key is next by a HTTP value
 */
void		CheckerTokens::checkHTTPKeyValuePairs( void )
{
	Token*		current = this->_head;

	while (current && current->getNext() && current->getNext()->getNext())
	{
		if (current->getType() == Token::HTTP_K)
		{
			Token*		next = current->getNext();

			if (next->getType() != Token::HTTP_V)
				throw CheckerError("Expected HTTP value after key " + current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check if a directive key is next by one or more directive values
 */
void		CheckerTokens::checkDirectiveKeyValuePairs(void)
{
	Token*		current = this->_head;

	while (current)
	{
		if (current->getType() == Token::DIR_K)
		{
			Token*		next = current->getNext();

			if (!next)
				throw CheckerError("Missing value after directive key " + current->getValue());
			while (next && (next->getType() == Token::DIR_V))
				next = next->getNext();
			if (!next || next->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after directive key-value(s) for " + current->getValue());
			current = next;
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon after directive value
 */
void		CheckerTokens::checkSemicolonAfterDirectiveValue( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_V && current->getNext()->getType() != Token::DIR_V)
			if (current->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after " + current->getValue());
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon after HTTP value
 */
void		CheckerTokens::checkSemicolonAfterHTTPValue( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::HTTP_V && current->getNext()->getType() != Token::HTTP_V)
			if (current->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after " + current->getValue());
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon before block end
 */
void		CheckerTokens::checkSemicolonBeforeBlockEnd( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if ((current->getType() == Token::LOC_BLK_E || 
			current->getType() == Token::ERR_BLK_E) &&
			current != this->_head)
		{
			Token*		prev = this->_head;

			while (prev->getNext()->getType() != current->getType())
				prev = prev->getNext();
			if (prev->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after value: " + current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check duplicated keys in the same scope
 */
void		CheckerTokens::checkDuplicatedKeysInScope( void )
{
	std::set<std::string>		seenKeys;
	Token*						current = this->_head;

	while (current)
	{
		if (current->getType() == Token::SERVER || 
			current->getType() == Token::LOC_BLK_S || 
			current->getType() == Token::ERR_BLK_S)
			seenKeys.clear();
		if (current->getType() == Token::DIR_K)
		{
			if (seenKeys.find(current->getValue()) != seenKeys.end())
				throw CheckerError("Duplicate directive: " + current->getValue());
			seenKeys.insert(current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check if the value of path start with a /
 */
void		CheckerTokens::checkpath( void )
{
	Token*		current = this->_head;

	while (current)
	{
		if (current->getType() == Token::LOCATION || current->getType() == Token::CGI_V)
			if (current->getValue()[0] != '/')
				throw CheckerError("Path must start with a /");
		if (current->getType() == Token::DIR_K && current->getValue() == "root")
		{
			current = current->getNext();
			if (current && current->getType() == Token::DIR_V)
				if (current->getValue()[0] != '/')
					throw CheckerError("Path of root directive must start with a /");
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the key and the value of the block error
 */
void		CheckerTokens::checkBlockError( void )
{
	Token*		current = this->_head;

	while (current)
	{
		if (current->getType() == Token::ERR_BLK_S)
			while (current && current->getType() != Token::ERR_BLK_E)
			{
				if (current->getType() == Token::DIR_V)
					if (current->getValue()[0] != '/')
						throw CheckerError("Path error must start with a /");
				current = current->getNext();
			}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the value of the directive
 */
void		CheckerTokens::checkValue( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getValue() == "autoindex")
		{
			std::string		val = current->getNext()->getValue();

			if (val != "on" && val != "off")
				throw CheckerError("value of \"autoindex\" not correct.");
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check all key of CGI start with a '.'
 */
void		CheckerTokens::checkCGI( void )
{
	Token*		current = this->_head;

	while (current->getType() != Token::CGI_BLK_S)
		current = current->getNext();
	while (current->getType() != Token::CGI_BLK_E)
	{
		if (current->getType() == Token::CGI_K)
			if (current->getValue()[0] != '.')
				throw CheckerError("CGI key must start with '.'");
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the method HTTP
 */
void		CheckerTokens::checkMethodHTTP( void )
{
	Token*		current = this->_head;
	
	while (current)
	{
		if (current->getType() == Token::HTTP_V)
			if (!MethodHTTP::isMethod(current->getValue()) && current->getValue() != "all")
				throw CheckerError("Method HTTP not valide: " + current->getValue());
		current = current->getNext();
	}
	return ;	
}

/*
 *	Check the final state of the tokens
 */
void		CheckerTokens::assertFinalState( void ) const
{
	if (this->_braceCount != 0)
		throw CheckerError("Mismatched braces");
	if (this->_inServer || this->_inLocation || this->_inErrorBlk)
		throw CheckerError("Unclosed block detected");
	return ;
}