/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:59 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:40:50 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerManager.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

/*
 *	Start all server
 */
void		ServerManager::startAll( void )
{
	std::set<Server*>::iterator		it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
		(*it)->start();
	return ;
}

/*
 *	Check if the port is valid for any server
 */
bool		ServerManager::isValidPort( size_t port ) const
{
	return (this->_mServers.find(port) != this->_mServers.end());
}