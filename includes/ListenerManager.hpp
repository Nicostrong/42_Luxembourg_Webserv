/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenerManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:20:44 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 23:37:42 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENERMANAGER_HPP
# define LISTENERMANAGER_HPP

#include "./lib.hpp"
#include "./Listener.hpp"
#include "./server/ServerManager.hpp"

class ListenerManager
{
    public:
        ListenerManager(ServerManager& sm, SocketManager& sockm, 
            EventMonitoring& em);
        ~ListenerManager();
    private:
        ListenerManager(const ListenerManager& obj);
        ListenerManager& operator=(const ListenerManager& obj);

        std::vector<Listener*>  _listeners;
}; 

#endif