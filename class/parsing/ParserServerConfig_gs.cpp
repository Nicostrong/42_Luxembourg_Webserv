/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig_gs.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:02:36 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:48:40 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ParserServerConfig.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Get the tokens list of the config file
 */
Token*		ParserServerConfig::getAllTokens( void ) const
{
	return (this->_allTokens);
}