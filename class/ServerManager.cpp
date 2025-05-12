/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/12 16:00:37 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerManager.hpp"

ServerManager::ServerManager(	const std::list<Token*>& serverListToken )
{
	std::list<Token*>::const_iterator		it;

	for (it = serverListToken.begin(); it != serverListToken.end(); it++)
	{
		Server*		server = new Server(it);

		addServer(server->getPort(), server);
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

void		ServerManager::addServer(int port, Server* server)
{
	this->_mServers[port] = server;
	return ;
}

Server*		ServerManager::getServer(int port) const 
{ 
	std::map<int, Server*>::const_iterator		it;
	
	it = this->_mServers.find(port);
	return ((it != this->_mServers.end()) ? it->second : NULL);
}
