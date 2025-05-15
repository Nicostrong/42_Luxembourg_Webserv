/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:12 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/15 09:30:42 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CheckerTokens.hpp"

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
 *								Method										   *
 ******************************************************************************/

/*
 *	Check the tokens of the config file
 */
void		CheckerTokens::check( Token* head )
{
	CheckerTokens	checker(head);
	
	checker.validate();
	return ;
}
