/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:59 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/04 15:20:45 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/ServerManager.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

/*
 *	Start all server
 */
void		ServerManager::startAll( void )
{
	/*std::set<Server*>::iterator		it;

	for (it = this->_sServers.begin(); it != this->_sServers.end(); ++it)
		(*it)->start();*/
	return ;
}

/*
 *	Check if the port is valid for any server
 */
bool		ServerManager::isValidPort( size_t port ) const
{
	return (this->_mServers.find(port) != this->_mServers.end());
}