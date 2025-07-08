/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:59 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 12:48:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/ServerManager.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

 /*
 *	Check if the port is valid for any server
 */
bool		ServerManager::isValidPort( size_t port ) const
{
	return (this->_mServers.find(port) != this->_mServers.end());
}