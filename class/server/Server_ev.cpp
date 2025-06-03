/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_ev.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:37:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/02 10:52:00 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Server.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		Server::start( void )
{
	sockaddr_in		addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);		//	NEED TO CREATE GETTER FOR PORT BUT WITCH
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
		close(serverSocket);
		return ;
	}

	if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "Socket failed to start listening" << std::endl;
		close(serverSocket);
		return ;
	}
	if (listen(serverSocket, 5) == -1)
	{
		std::cerr << "Socket failed to start listening" << strerror(errno) << std::endl;
		close(serverSocket);
		return ;
	}

	std::cout << "Listening on port 8080" << std::endl;		//	NEED TO CALL GETTER FOR PORT
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
		EventData::CLIENT, this->_lSockets.front());
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