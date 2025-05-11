/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:12 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/11 17:29:09 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CheckerTokens.hpp"

CheckerTokens::CheckerTokens( Token* head ) : _head(head), _braceCount(0),
											_inServer(false), _inLocation(false),
											_inErrorBlk(false)
{
	LOG_DEB("Constructor CheckerTokens");
	return ;
}

CheckerTokens::~CheckerTokens( void )
{
	LOG_DEB("Destructor CheckerTokens");
	return ;
}

void		CheckerTokens::validate( void )
{
	checkBracesAndBlocks();
	checkDirectiveKeyValuePairs();
	checkSemicolonAfterDirectiveValue();
	checkSemicolonBeforeBlockEnd();
	checkDuplicatedKeysInScope();
	checkValue();
	checkMethodHTTP();
	assertFinalState();
	return ;
}

void		CheckerTokens::checkBracesAndBlocks( void )
{
	Token*		current = this->_head;

	while (current)
	{
		switch (current->getType())
		{
			case Token::SERVER:
				if (this->_inServer)
					throw CheckerError("Nested server block not allowed");
				break;
			case Token::SER_BLK_S:
				this->_inServer = true;
				this->_braceCount++;
				break;
			case Token::SER_BLK_E:
				this->_braceCount--;
				if (this->_braceCount < 0)
					throw CheckerError("Too many closing braces");
				if (this->_inLocation || this->_inErrorBlk)
					throw CheckerError("Unexpected closing brace");
				else if (this->_inServer)
					this->_inServer = false;
				else
					throw CheckerError("Unexpected closing brace");
				break;

			case Token::LOCATION:
				if (this->_inLocation)
					throw CheckerError("Nested location block not allowed");
				break;
			case Token::LOC_BLK_S:
				if (!this->_inServer)
					throw CheckerError("Location block outside server");
				if (this->_inLocation)
					throw CheckerError("Nested location not allowed");
				this->_inLocation = true;
				break;
			case Token::LOC_BLK_E:
				this->_braceCount--;
				if (this->_braceCount < 0)
					throw CheckerError("Too many closing braces");
				if (this->_inErrorBlk)
					throw CheckerError("Unexpected closing brace");
				else if (this->_inLocation)
					this->_inLocation = false;
				else
					throw CheckerError("Unexpected closing brace");
				break;
			
			case Token::ERROR:
				if (this->_inErrorBlk)
					throw CheckerError("Nested error block not allowed");
				break;
			case Token::ERR_BLK_S:
				if (!this->_inServer)
					throw CheckerError("Error_page block outside server");
				if (this->_inErrorBlk || this->_inLocation)
					throw CheckerError("Nested error_page not allowed");
				this->_inErrorBlk = true;
				break;
			case Token::ERR_BLK_E:
				this->_braceCount--;
				if (this->_braceCount < 0)
					throw CheckerError("Too many closing braces");
				if (this->_inLocation)
					throw CheckerError("Unexpected closing brace");
				else if (this->_inErrorBlk)
					this->_inErrorBlk = false;
				else
					throw CheckerError("Unexpected closing brace");
				break;

			default:
				break;
		}
		current = current->getNext();
	}
	return ;
}

void		CheckerTokens::checkDirectiveKeyValuePairs( void )
{
	Token*		current = _head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_K || 
			current->getType() == Token::HTTP_K)
		{
			Token*		next = current->getNext();

			if (next->getType() != Token::DIR_V && next->getType() != Token::HTTP_V)
				throw CheckerError("Expected directive or HTTP value after key");
		}
		current = current->getNext();
	}
	return ;
}

void		CheckerTokens::checkSemicolonAfterDirectiveValue( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_V || current->getType() == Token::HTTP_V)
		{
			Token*		next = current->getNext();

			if (next->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after directive or method value");
		}
		current = current->getNext();
	}
	return ;
}

void		CheckerTokens::checkSemicolonBeforeBlockEnd( void )
{
	Token*		current = this->_head;

	while (current && current->getNext())
	{
		if ((current->getType() == Token::LOC_BLK_E || current->getType() == Token::ERR_BLK_E) &&
			current != this->_head)
		{
			Token*		prev = this->_head;

			while (prev->getNext() != current)
				prev = prev->getNext();
			if (prev->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' before closing location or error block");
		}
		current = current->getNext();
	}
	return ;
}

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

void		CheckerTokens::checkMethodHTTP( void )
{
	Token*		current = this->_head;

	while (current)
	{
		if (current->getType() == Token::HTTP_V)
			if (!MethodHTTP::isMethod(current->getValue()))
				throw CheckerError("Method HTTP not valide.");
		current = current->getNext();
	}
	return ;	
}

void		CheckerTokens::assertFinalState( void ) const
{
	if (_braceCount != 0)
		throw CheckerError("Mismatched braces");
	if (_inServer || _inLocation || _inErrorBlk)
		throw CheckerError("Unclosed block detected");
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsing error with data
 */
CheckerTokens::CheckerError::CheckerError( const std::string &data ) throw()
{
	this->_msg = RED"[ERROR] Checker error: " + data + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
CheckerTokens::CheckerError::~CheckerError( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char		*CheckerTokens::CheckerError::what() const throw()
{
	return (this->_msg.c_str());
}
