/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 23:18:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "lib.hpp"
#include "Ip.hpp"
#include "EventMonitoring.hpp"
#include "Socket.hpp"
#include "SocketManager.hpp"
#include "server/ServerManager.hpp"
#include "IEventHandler.hpp"
#include "Endpoint.hpp"

class Listener : public IEventHandler
{
    public:
        Listener(const Endpoint& addr, SocketManager& sockm, 
                ServerManager& servm);
        ~Listener();
        bool    		listenSocket(EventMonitoring& em);

		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
    private:
		Listener(const Listener& obj);
		Listener& operator=(const Listener& obj);
		
        const Endpoint&             _addr;
		int				            _serverSocket;
		SocketManager&	            _sockm;
        ServerManager&              _servm;
};

#endif