/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:35:58 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENER_HPP
# define LISTENER_HPP

# include "./Socket.hpp"
# include "./../lib.hpp"
# include "./../utils/Ip.hpp"
# include "./../utils/Fd.hpp"
# include "./SocketManager.hpp"
# include "./../utils/Endpoint.hpp"
# include "./../events/IEventHandler.hpp"
# include "./../server/ServerManager.hpp"
# include "./../events/EventMonitoring.hpp"

class   Listener : public   IEventHandler
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