/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/30 13:59:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/ServerManager.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	ServerManager constructor with a list of Token in argument
 */
ServerManager::ServerManager( Token* allTokens, EventMonitoring& eventMonitoring )
	: _nbServer(0)
{
	try
	{
		std::list<Token*>::const_iterator		it;

		splitServerToken(allTokens);
		for (it = this->_lServerToken.begin(); it != this->_lServerToken.end(); ++it)
		{
			Token*									tokens;
			Server*									server;
			std::list<size_t>						ports;
			std::list<size_t>::const_iterator		pit;

			tokens = *it;
			server = new Server(tokens, eventMonitoring);
			ports = server->getPortList();
			for (pit = ports.begin(); pit != ports.end(); ++pit)
				this->_mServers[*pit].push_back(server);
			this->_sServers.insert(server);
			this->_nbServer++;
		}
	}
	catch(const std::exception& e)
	{
		cleanRessources();
		throw ;
	}
	return ;
}

/*
 *	ServerManager destructor delete all pointer of Server object
 */
ServerManager::~ServerManager( void )
{
	cleanRessources();
	return ;
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/
