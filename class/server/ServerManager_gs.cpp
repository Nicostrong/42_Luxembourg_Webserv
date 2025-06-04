/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_gs.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:32:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/04 23:26:34 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/ServerManager.hpp"

/*******************************************************************************
 *								GETTER										   *
******************************************************************************/

/*
*	get the server matchin with the port and host
*/
const Server*		ServerManager::getServer( size_t port, std::string host ) const
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

/*	retourne un set d ip:port de tout les servers de la config */
const std::set<std::pair< Ip , size_t> >	ServerManager::getSocketSet( void ) const
{
	std::set<std::pair<Ip, size_t> >						retSet;
	std::map<size_t, std::vector<Server*> >::const_iterator		itMap;

	for (itMap = this->_mServers.begin(); itMap != this->_mServers.end(); ++itMap)
	{
		std::vector<Server* >::const_iterator		itVec;

		for (itVec = itMap->second.begin(); itVec != itMap->second.end(); ++itVec)
			retSet.insert(std::make_pair((*itVec)->getIp(), itMap->first));
	}
	return (retSet);
}

/*	rertourne le server qui match avec host, ip et hostname	*/
const Server*		ServerManager::getMatchingServer( const Ip& ip, size_t port, const std::string& host ) const
{
	std::map<size_t, std::vector<Server*> >::const_iterator		findIt;
	const Server*												defaultServer = NULL;
	const Server*												ipMatchServer = NULL;
	std::vector<Server*>::const_iterator						serverIt;

	findIt = _mServers.find(port);
	if (findIt == _mServers.end()) 
		return (NULL);

	for (serverIt = findIt->second.begin(); serverIt != findIt->second.end(); ++serverIt)
	{
		const Server*								server = *serverIt;
		const std::list<std::string>&				hostList = server->getHost();
		std::list<std::string>::const_iterator		hostIt;

		for (hostIt = hostList.begin(); hostIt != hostList.end(); ++hostIt)
		{
			if (*hostIt == host)
			{
				if (server->getIp().getIpBytes() == ip.getIpBytes())
					return (server);
				else if (server->getIp().getIpString() == "0.0.0.0") 
					ipMatchServer = server;
			}
		}
		if (!defaultServer) 
			defaultServer = server;
	}
	return (ipMatchServer ? ipMatchServer : defaultServer);
}

/*	ADD SOME GETTER A CHECKER	*/
const Location*		ServerManager::getLocationForUri( const Server* server, const std::string& uri ) const
{
	const std::map<std::string, Location*>&					locations = server->getAllLocation();
	std::map<std::string, Location*>::const_iterator		it = locations.begin();
	const Location*											matched = NULL;

	for (; it != locations.end(); ++it)
		if (it->second->isMatching(uri))
			if (!matched || it->first.length() > matched->getPath().length())
				matched = it->second;
	return (matched);
}

size_t		ServerManager::getMaxBodySize( const Server* server, const Location* location ) const
{
	const Directive*		directive = location->findDirective("client_max_body_size");
	
	if (directive && !directive->getValue().empty())
		return (static_cast<size_t>(std::atoi(directive->getValue().c_str())));
	return (server->getMaxSizeBody());
}

std::string		ServerManager::getRoot( const Location* location ) const
{
	const Directive*		directive = location->findDirective("root");

	if (directive)
		return (directive->getValue());
	return ("");
}

std::string		ServerManager::getIndexFile( const Location* location ) const
{
	const Directive*		directive = location->findDirective("index");

	if (directive)
		return (directive->getValue());
	return ("index.html"); // valeur par défaut a lire dans server directive index
}

bool		ServerManager::isMethodAllowed( const Location* location, const std::string& method ) const
{
	const MethodHTTP*		methods = location->getMethod();

	if (!methods)
		return (false);
	return (methods->isAllowed(method));
}

bool		ServerManager::doesPathExist( const std::string& path ) const
{
	struct stat		st;

	return (stat(path.c_str(), &st) == 0);
}

bool		ServerManager::isBodyTooLarge( size_t bodySize, size_t maxSize ) const
{
	return (bodySize > maxSize);
}

bool		ServerManager::isAutoIndexEnabled( const Location* location ) const
{
	const Directive*		directive = location->findDirective("autoindex");

	if (directive && directive->getValue() == "on")
		return (true);
	return (false);
}