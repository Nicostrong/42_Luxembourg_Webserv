/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 22:49:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERLISTENER_HPP
#define SERVERLISTENER_HPP

#include "lib.hpp"
#include "Ip.hpp"
#include "EventMonitoring.hpp"
#include "Socket.hpp"
#include "IEventHandler.hpp"

class ServerListener : public IEventHandler
{
    public:
        ServerListener(const Ip& ip, size_t port, std::vector<Socket*>& sockets);
        ~ServerListener();
        bool    		listenSocket(EventMonitoring& em);

		void onReadEvent(int fd, int type, EventMonitoring& em);
		void onWriteEvent(int fd, int type, EventMonitoring& em);
		void onCloseEvent(int fd, int type, EventMonitoring& em);
    private:
		ServerListener(const ServerListener& obj);
		ServerListener& operator=(const ServerListener& obj);
		
        Ip						_ip;
        size_t					_port;
		int						_serverSocket;
		std::vector<Socket*>&	_sockets;
};

#endif