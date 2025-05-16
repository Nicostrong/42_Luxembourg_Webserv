/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:34:47 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGIDirective.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
CGIDirective::CGIDirective( Token*& tokens) 
{
	if (tokens->getType() != Token::CGI_K)
		throw BadTokenType();
	this->_extension = tokens->getValue();
	tokens = tokens->getNext();
	if (!tokens || tokens->getType() != Token::CGI_V)
		throw BadTokenType();
	this->_path = tokens->getValue();
	return ;
}

/*
 *	Default destructor
 */
CGIDirective::~CGIDirective( void )
{
	return ;
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/