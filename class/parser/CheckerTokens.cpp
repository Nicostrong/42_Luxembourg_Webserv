/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:12 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/20 12:55:42 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Constructor CheckerTokens
 */
CheckerTokens::CheckerTokens( const Token& head ) : _head(&head), _braceCount(0),
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
