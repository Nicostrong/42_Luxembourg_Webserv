/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:12 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/10 17:52:25 by nicostrong       ###   Luxembourg.lu     */
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
					throw ParserServerConfig::ParsingError("Nested server block not allowed");
				this->_inServer = true;
				break;

			case Token::BRACE_S:
				this->_braceCount++;
				break;

			case Token::BRACE_E:
				this->_braceCount--;
				if (this->_braceCount < 0)
					throw ParserServerConfig::ParsingError("Too many closing braces");
				if (this->_inLocation)
					this->_inLocation = false;
				else if (this->_inErrorBlk)
					this->_inErrorBlk = false;
				else if (this->_inServer)
					this->_inServer = false;
				else
					throw ParserServerConfig::ParsingError("Unexpected closing brace");
				break;

			case Token::LOC_BLK_S:
				if (!this->_inServer)
					throw ParserServerConfig::ParsingError("Location block outside server");
				if (this->_inLocation)
					throw ParserServerConfig::ParsingError("Nested location not allowed");
				this->_inLocation = true;
				break;

			case Token::ERR_BLK_S:
				if (!this->_inServer)
					throw ParserServerConfig::ParsingError("Error_page block outside server");
				if (this->_inErrorBlk)
					throw ParserServerConfig::ParsingError("Nested error_page not allowed");
				this->_inErrorBlk = true;
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
			current->getType() == Token::ERR_K || 
			current->getType() == Token::HTTP_K)
		{
			Token*		next = current->getNext();

			if (next->getType() != Token::DIR_V && next->getType() != Token::HTTP_V)
				throw ParserServerConfig::ParsingError("Expected directive or HTTP value after key");
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
				throw ParserServerConfig::ParsingError("Expected ';' after directive or method value");
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
				throw ParserServerConfig::ParsingError("Expected ';' before closing location or error block");
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
				throw ParserServerConfig::ParsingError("Duplicate directive: " + current->getValue());
			seenKeys.insert(current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

void		CheckerTokens::assertFinalState( void ) const
{
	if (_braceCount != 0)
		throw ParserServerConfig::ParsingError("Mismatched braces");
	if (_inServer || _inLocation || _inErrorBlk)
		throw ParserServerConfig::ParsingError("Unclosed block detected");
	return ;
}
