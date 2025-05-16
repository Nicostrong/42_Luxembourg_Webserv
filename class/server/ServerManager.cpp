/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 13:42:25 by nicostrong       ###   Luxembourg.lu     */
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
			Token*									tokens;
			Server*									server;
			std::list<size_t>						ports;
			std::list<size_t>::const_iterator		pit;

			tokens = *it;
			server = new Server(tokens, eventMonitoring);
			ports = server->getPortList();
			for (pit = ports.begin(); pit != ports.end(); ++pit)
				this->_mServers[*pit] = server;
			this->_servers.insert(server);
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
	std::set<Server*>::iterator		it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
		delete *it;
	this->_mServers.clear();
	this->_servers.clear();
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

const std::map<size_t, Server*>&		ServerManager::getServers( void ) const
{
	return (this->_mServers);
}

Server*		ServerManager::getServer( size_t port) const 
{ 
	if (isValidPort(port))
		return (this->_mServers.find(port)->second);
	return (this->_mServers.begin()->second);
}

int			ServerManager::getNbServer( void ) const
{
	return (this->_nbServer);
}

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

void		ServerManager::startAll( void )
{
	std::set<Server*>::iterator		it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
		(*it)->start();
	return ;
}

bool		ServerManager::isValidPort( size_t port ) const
{
	return (this->_mServers.find(port) != this->_mServers.end());
}