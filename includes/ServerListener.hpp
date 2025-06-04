/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 21:06:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERLISTENER_HPP
#define SERVERLISTENER_HPP

#include "lib.hpp"
#include "Ip.hpp"
#include "EventMonitoring.hpp"
#include "Socket.hpp"
#include "SocketManager.hpp"
#include "server/ServerManager.hpp"
#include "IEventHandler.hpp"
#include "Endpoint.hpp"

class ServerListener : public IEventHandler
{
    public:
        ServerListener(const std::pair<Ip, size_t>& addr, SocketManager& sockm, 
                ServerManager& servm);
        ~ServerListener();
        bool    		listenSocket(EventMonitoring& em);

		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
    private:
		ServerListener(const ServerListener& obj);
		ServerListener& operator=(const ServerListener& obj);
		
        const std::pair<Ip, size_t> _addr;
		int				            _serverSocket;
		SocketManager&	            _sockm;
        ServerManager&              _servm;
};

#endif