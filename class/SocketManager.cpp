/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 10:33:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/SocketManager.hpp"

SocketManager::SocketManager()
{
	this->_sockets.reserve(MAX_CLIENT);
}

SocketManager::~SocketManager()
{
	//Should close all sockets
}

void SocketManager::add(Socket& sock, EventMonitoring& em)
{
	em.monitor(sock.getSocket(), POLLIN | POLLHUP | POLLRDHUP,
		EventData::CLIENT, sock);
	
	this->_sockets.push_back(&sock);
}