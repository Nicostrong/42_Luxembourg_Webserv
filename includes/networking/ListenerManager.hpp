/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenerManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:20:44 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:36:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENERMANAGER_HPP
# define LISTENERMANAGER_HPP

# include "./../lib.hpp"
# include "./Listener.hpp"
# include "./../server/ServerManager.hpp"

class   ListenerManager
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