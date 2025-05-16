/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_gs.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 17:15:59 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerManager.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

 /*
  *	get the server matchin with the port and host
  */
Server*		ServerManager::getServer( size_t port, std::string host ) const
{
	std::map<size_t, std::vector<Server*> >::const_iterator		it;
	
	if (!isValidPort(port))
		return (NULL);		//	Avoir si on jete pas une exception ici
	it = this->_mServers.find(port);
	if (it == this->_mServers.end())
	{
		return (NULL);
	}
	
	const std::vector<Server*>&		servers = it->second;

	for (size_t i = 0; i < servers.size(); ++i)
		if (servers[i]->matchHost(host))
			return (servers[i]);
	return (servers.front());
}

/*
 *	Get all server for a specific port
 */
const std::set<Server*>&		ServerManager::getAllServers( void ) const
{
	return (this->_sServers);
}

/*
 *	Get all server for a specific port
 */
std::vector<Server*>		ServerManager::getAllServersForPort( size_t port ) const
{
	std::map<size_t, std::vector<Server*> >::const_iterator		it;
	
	it = this->_mServers.find(port);
	if (it != this->_mServers.end())
		return (it->second);
	return (std::vector<Server*>());
}

/*
 *	Get the number of server on the config
 */
int			ServerManager::getNbServer( void ) const
{
	return (this->_nbServer);
}