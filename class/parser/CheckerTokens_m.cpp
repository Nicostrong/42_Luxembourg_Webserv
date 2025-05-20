/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:03:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/20 07:14:26 by nicostrong       ###   Luxembourg.lu     */
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