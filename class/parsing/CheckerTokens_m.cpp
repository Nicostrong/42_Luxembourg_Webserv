/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:03:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:03:41 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CheckerTokens.hpp"

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