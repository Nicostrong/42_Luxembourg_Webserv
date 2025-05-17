/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:27:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:50:02 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Directive.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Directive::Directive( Token*& directiveTokens )
{
	std::string					key = directiveTokens->getValue();
	std::list<std::string>		lValue;

	while (directiveTokens && directiveTokens->getType() != Token::SEMICOLON)
	{
		if (directiveTokens->getType() == Token::DIR_V)
			lValue.push_back(directiveTokens->getValue());
		directiveTokens = directiveTokens->getNext();
	}
	if (key.empty() || lValue.empty())
		throw FieldsEmpty();
	this->_key = key;
	this->_lValue = lValue;
	return ;
}

/*
 *	Default destructor
 */
Directive::~Directive( void )
{
	return ;
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/