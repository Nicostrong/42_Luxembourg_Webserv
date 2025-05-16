/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_gs.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:29:11 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerManager.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

 /*
  *	get the server matchin with the port and host
  */
Server*		ServerManager::getServers( size_t port, std::string host ) const
{
	std::map<size_t, std::vector<Server*> >::const_iterator		it;
	const std::vector<Server*>&									servers;
	
	if (!isValidPort(port))
		return (NULL);		//	Avoir si on jete pas une exception ici
	it = this->_mServers.find(port);
	servers = it->second;
	for (size_t i = 0; i < servers.size(); ++i)
		if (servers[i]->matchHost(host))
			return (servers[i]);
	return (servers.front());
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
	return (NULL);
}
/*
 *	Get the number of server on the config
 */
int			ServerManager::getNbServer( void ) const
{
	return (this->_nbServer);
}