/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenerManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:16:22 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:50:00 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/networking/ListenerManager.hpp"

ListenerManager::ListenerManager(ServerManager& sm, SocketManager& sockm, 
    EventMonitoring& em)
{
    const std::set<std::pair<Ip, size_t> > endpoints = sm.getSocketSet();
    std::set<std::pair<Ip, size_t> >::const_iterator it;
    
    this->_listeners.reserve(endpoints.size());
    for (it = endpoints.begin(); it != endpoints.end(); ++it)
		{
			Listener* listener = 
                new Listener(Endpoint(it->first, it->second), sockm, sm);
			
			if (listener)
            {
				this->_listeners.push_back(listener);
			    listener->listenSocket(em);
            }
		}
}

ListenerManager::~ListenerManager()
{
    std::vector<Listener*>::const_iterator it;

    for (it = this->_listeners.begin(); it !=  this->_listeners.end(); ++it)
	    delete *it;
}