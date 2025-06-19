/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:57:33 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "./../lib.hpp"
#include "./../utils/Ip.hpp"
#include "./../utils/Endpoint.hpp"
#include "./../events/EventMonitoring.hpp"
#include "./../events/IEventHandler.hpp"
#include "./../server/ServerManager.hpp"
#include "./Socket.hpp"
#include "./SocketManager.hpp"

class Listener : public IEventHandler
{
    public:
        Listener(const Endpoint& addr, SocketManager& sockm, 
                ServerManager& servm);
        ~Listener();
        bool    		listenSocket(EventMonitoring& em);

		void onReadEvent(int fd, EventMonitoring& em);
		void onWriteEvent(int fd, EventMonitoring& em);
		void onCloseEvent(int fd, EventMonitoring& em);
		void onTickEvent(int fd, EventMonitoring& em);
    private:
		Listener(const Listener& obj);
		Listener& operator=(const Listener& obj);
		
        const Endpoint              _addr;
		int				            _serverSocket;
		SocketManager&	            _sockm;
        ServerManager&              _servm;
};

#endif