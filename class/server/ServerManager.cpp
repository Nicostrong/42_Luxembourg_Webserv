/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 10:32:13 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerManager.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	ServerManager constructor with a list of Token in argument
 */
ServerManager::ServerManager(	const std::list<Token*>& serverListToken,
								EventMonitoring& eventMonitoring  )
	: _nbServer(0)
{
	try
	{
		std::list<Token*>::const_iterator		it;

		for (it = serverListToken.begin(); it != serverListToken.end(); ++it)
		{
			Token*		tokens = *it;
			Server*		server = new Server(tokens, eventMonitoring);

			this->_mServers[server->getPort()] = server;
			this->_nbServer++;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	ServerManager destructor delete all pointer of Server object
 */
ServerManager::~ServerManager( void )
{
	std::map<int, Server*>::iterator		it;

	for (it = this->_mServers.begin(); it != this->_mServers.end(); ++it)
		delete it->second;
	this->_mServers.clear();
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

const std::map<int, Server*>&		ServerManager::getServers( void ) const
{
	return (this->_mServers);
}

Server*								ServerManager::getServer(int port) const 
{ 
	std::map<int, Server*>::const_iterator		it;
	
	it = this->_mServers.find(port);
	return ((it != this->_mServers.end()) ? it->second : NULL);
}

int									ServerManager::getNbServer( void ) const
{
	return (this->_nbServer);
}

void								ServerManager::startAll( void )
{
	std::map<int, Server*>::iterator		it;

	for (it = this->_mServers.begin(); it != this->_mServers.end(); ++it)
		it->second->start();
	return ;
}