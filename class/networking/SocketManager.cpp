/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 17:15:54 by nfordoxc         ###   Luxembourg.lu     */
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
	em.monitor(sock.getSocket(), EPOLLIN | EPOLLTICK | EPOLLHUP | EPOLLRDHUP, sock);
	sock.setEM(em);
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