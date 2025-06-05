/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:39:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:12:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/networking/Listener.hpp"


Listener::Listener(const Endpoint& addr, 
	SocketManager& sockm, ServerManager& servm) 
	: _addr(addr), _serverSocket(-1), _sockm(sockm), _servm(servm) {}

Listener::~Listener() 
{
	if (this->_serverSocket > 2)
		close(this->_serverSocket);
}

bool Listener::listenSocket(EventMonitoring& em)
{
    sockaddr_in		addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_addr.getPort());
	addr.sin_addr.s_addr = this->_addr.getIp().getIpBytes();

    try
    {
        this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->_serverSocket == -1)
        	throw std::runtime_error("Failed to listen");

        int opt = 1;
        if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
        	throw std::runtime_error("Failed to listen");

        if (bind(this->_serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        	throw std::runtime_error("Failed to listen");
        
        if (listen(this->_serverSocket, 16) == -1)
			throw std::runtime_error("Failed to listen");

        std::cout << "Listening to " << this->_addr.getIp().getIpString() 
                << ":" <<this->_addr.getPort() << std::endl;
        em.monitor(this->_serverSocket, POLLIN, EventData::SERVER, 
            *this);
        return (true);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed to listen to " << this->_addr.getIp().getIpString() 
                    << ":" << this->_addr.getPort() << std::endl;

        if (this->_serverSocket > 2)
            close(this->_serverSocket);
    }
    return (false);
}

// Socket events

void Listener::onReadEvent(int fd, int type, EventMonitoring& em)
{
	(void)fd;
	(void)type;
	sockaddr_in	clientAddr;
	socklen_t addrLen = sizeof(clientAddr);
	Socket* sock = NULL;
		
	int clientSocket = accept(this->_serverSocket, 
		(struct sockaddr*)&clientAddr, &addrLen);
	
	try
	{
		if (clientSocket == -1)
			throw std::runtime_error("Failed to accept client");

		sock = new Socket(clientSocket, 
			Endpoint::getEndpoint(clientAddr),
			Endpoint::getEntryAddress(clientSocket),
			this->_servm, 
			this->_sockm);

		if (!sock)
			throw std::runtime_error("Failed to accept client");

		this->_sockm.add(*sock, em);
	}
	catch(const std::exception& e)
	{
		if (sock)
			delete sock;
		else if (clientSocket > 2)
			close(clientSocket);
		
		std::cerr << "Failed to accept client" << std::endl;
	}
}

void Listener::onWriteEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}

void Listener::onCloseEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}
