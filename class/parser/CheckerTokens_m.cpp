/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:03:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/20 12:41:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

/*******************************************************************************
 *								Method										   *
 ******************************************************************************/

/*
 *	Check the tokens of the config file
 */
void		CheckerTokens::check( const Token& head )
{
	CheckerTokens	checker(head);
	
	try
	{
		checker.validateTokens();
	}
	catch(const std::exception& e)
	{
		throw ;
	}
	return ;
}