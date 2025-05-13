/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:58:34 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerManager.hpp"

ServerManager::ServerManager(	const std::list<Token*>& serverListToken,
								EventMonitoring& eventMonitoring  )
	: _nbServer(0)
{
	std::list<Token*>::const_iterator		it;

	for (it = serverListToken.begin(); it != serverListToken.end(); ++it)
	{
		Server*		server = new Server(*it, eventMonitoring);

		this->_mServers[server->getPort()] = server;
		this->_nbServer++;
	}
	return ;
}

ServerManager::~ServerManager( void )
{
	std::map<int, Server*>::iterator		it;

	for (it = this->_mServers.begin(); it != this->_mServers.end(); ++it)
		delete it->second;
	this->_mServers.clear();
	return ;
}

const std::map<int, Server*>& ServerManager::getServers() const
{
	return (this->_mServers);
}

Server*		ServerManager::getServer(int port) const 
{ 
	std::map<int, Server*>::const_iterator		it;
	
	it = this->_mServers.find(port);
	return ((it != this->_mServers.end()) ? it->second : NULL);
}

int			ServerManager::getNbServer( void )
{
	return (this->_nbServer);
}