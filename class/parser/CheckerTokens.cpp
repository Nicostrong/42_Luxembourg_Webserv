/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:12 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/17 11:47:22 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Constructor CheckerTokens
 */
CheckerTokens::CheckerTokens( Token* head ) : _head(head), _braceCount(0),
											_inServer(false), _inLocation(false),
											_inErrorBlk(false), _inCGI(false)
{
	return ;
}

/*
 *	Destructor CheckerTokens
 */
CheckerTokens::~CheckerTokens( void )
{
	return ;
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/
