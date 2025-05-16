/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig_gs.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:02:36 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:40:02 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ParserServerConfig.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Get the tokens list of the config file
 */
const Token*&		ParserServerConfig::getAllTokens( void ) const
{
	return (this->_allTokens);
}