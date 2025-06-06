/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:12:51 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/networking/SocketManager.hpp"

SocketManager::SocketManager()
{
	this->_sockets.reserve(MAX_CLIENT);
}

SocketManager::~SocketManager()
{
	std::vector<Socket*>::iterator it;

	for (it = this->_sockets.begin(); it != this->_sockets.end(); ++it)
		delete *it;
}

void SocketManager::add(Socket& sock, EventMonitoring& em)
{
	em.monitor(sock.getSocket(), POLLIN | POLLHUP | POLLRDHUP,
		EventData::CLIENT, sock);
	
	this->_sockets.push_back(&sock);
}

void SocketManager::remove(Socket& sock, EventMonitoring& em)
{
	em.unmonitor(sock.getSocket());

	std::vector<Socket*>::iterator it;

	for (it = this->_sockets.begin(); it != this->_sockets.end(); ++it)
	{
		if (*it == &sock)
		{
			delete *it;
			this->_sockets.erase(it);
			return ;
		}
	}
}