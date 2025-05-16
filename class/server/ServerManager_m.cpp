/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_m.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:59 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 17:19:34 by nicostrong       ###   Luxembourg.lu     */
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

	for (it = this->_sServers.begin(); it != this->_sServers.end(); ++it)
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