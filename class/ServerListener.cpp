/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:39:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 23:00:58 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ServerListener.hpp"


ServerListener::ServerListener(const Ip& ip, size_t port,
	std::vector<Socket*>& sockets) 
	: _ip(ip), _port(port), _serverSocket(-1), _sockets(sockets) {}

ServerListener::~ServerListener() {}

bool ServerListener::listenSocket(EventMonitoring& em)
{
    sockaddr_in		addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port);
	addr.sin_addr.s_addr = this->_ip.getIpBytes();

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

        std::cout << "Listening to " << this->_ip.getIpString() 
                << ":" << this->_port << std::endl;
        em.monitor(this->_serverSocket, POLLIN, EventData::SERVER, 
            *this);
        return (true);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed to listen to " << this->_ip.getIpString() 
                    << ":" << this->_port << std::endl;

        if (this->_serverSocket > 2)
            close(this->_serverSocket);
    }
    return (false);
}

// Socket events

void ServerListener::onReadEvent(int fd, int type, EventMonitoring& em)
{
	sockaddr_in	clientAddr;
	socklen_t addrLen = sizeof(clientAddr);
	
	int clientSocket = accept(this->_serverSocket, 
		(struct sockaddr*)&clientAddr, &addrLen);
		
	if (clientSocket == -1)
		return ;
	
	Socket*		s = new Socket(clientSocket, em, NULL, clientAddr);

	if (!s)
	{
		close(clientSocket);
		return ;
	}

	this->_sockets.push_back(s);

	em.monitor(clientSocket, POLLIN | POLLHUP | POLLRDHUP,
		EventData::CLIENT, *s);
}

void ServerListener::onWriteEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}

void ServerListener::onCloseEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}
