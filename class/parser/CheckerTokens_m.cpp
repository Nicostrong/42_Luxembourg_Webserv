/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:03:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:47:01 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

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