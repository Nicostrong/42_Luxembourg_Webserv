/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_ev.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:37:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 22:04:34 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		Server::start( void )
{
	sockaddr_in		addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->getPort());
	addr.sin_addr.s_addr = INADDR_ANY;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Socket failed to be created" << std::endl;
		return ;
	}

	int opt = 1;

	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		std::cerr << "Setsockopt failed: " << strerror(errno) << std::endl;
		return ;
	}

	if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "Socket failed to start listening" << std::endl;
		return ;
	}
	if (listen(serverSocket, 5) == -1)
	{
		std::cerr << "Socket failed to start listening" << strerror(errno) << std::endl;
		return ;
	}

	std::cout << "Listening on port " << this->_port << std::endl;
	this->_serverSocket = serverSocket;
	this->_em.monitor(serverSocket, POLLIN, EventData::SERVER, 
		*this);
	return ;
}

void		Server::onReadEvent( int fd, int type, EventMonitoring& em )
{
	(void)fd;
	(void)type;

	struct sockaddr_in		clientAddr;
	socklen_t				addrLen = sizeof(clientAddr);
	
	int clientSocket = accept(this->_serverSocket, 
		(struct sockaddr*)&clientAddr, &addrLen);
	if (clientSocket == -1)
		return;
	
	Socket		s(clientSocket, em, *this, clientAddr);

	this->_lSockets.push_front(s);
	em.monitor(clientSocket, POLLIN | POLLHUP | POLLRDHUP,
		EventData::CLIENT, *_lSockets.begin());
	return ;
}

void		Server::onWriteEvent( int fd, int type, EventMonitoring& em )
{
	(void)em;
	(void)fd;
	(void)type;
	return ;
}

void		Server::onCloseEvent( int fd, int type, EventMonitoring& em )
{
	(void)em;
	(void)fd;
	(void)type;
	return ;
}

void		Server::onSocketClosedEvent( const Socket& s )
{
	this->_em.unmonitor(s.getSocket());
	close(s.getSocket());
	this->_lSockets.remove(s);
	std::cout << "A client has disconnected" << std::endl;
	return ;
}