/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:49:32 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/CGIDirective.hpp"

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