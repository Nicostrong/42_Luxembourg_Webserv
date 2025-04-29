/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:52:16 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 14:49:13 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include "../includes/HttpRequest.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/EventHandler.hpp"
#include "../includes/ClientData.hpp"

#define MAX_CONNECTIONS 20

int main()
{
	EventMonitoring pmonitoring;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	// std::vector<pollfd> fds(MAX_CONNECTIONS);

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Socket failed to be created" << std::endl;
		return (1);
	}

	int opt = 1;

	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		std::cerr << "Setsockopt failed: " << strerror(errno) << std::endl;
		return 1;
	}

	if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "Socket failed to start listening" << std::endl;
		return (1);
	}
	if (listen(serverSocket, 5) == -1)
	{
		std::cerr << "Socket faield to start listening" << strerror(errno) << std::endl;
		return (1);
	}

	pmonitoring.monitor(serverSocket, POLLIN, EventHandler::SERVER);
	std::cout << "Listening on port 8080" << std::endl;

	int amount = 0;
	while ((amount = pmonitoring.update()) != -1)
	{
		const std::vector<epoll_event> events = pmonitoring.getEvents();
		std::vector<epoll_event>::const_iterator it;

		for (it = events.begin(); it != events.begin() + amount; it++)
		{
			EventHandler<> *data = static_cast<EventHandler *>(it->data.ptr);
			if (it->events & (POLLERR | POLLHUP | POLLRDHUP))
			{
				close(data->getFd());
				pmonitoring.unmonitor(data->getFd());
				std::cout << "Socket closed by remote" << std::endl;
				std::cout << pmonitoring.getClientsConnected() 
						  << " clients connected." << std::endl; 
				continue;
			}
			switch (data->getType())
			{
				case EventHandler::SERVER:
				{
					if (it->events & POLLIN)
					{
						int clientSocket = accept(serverSocket, NULL, NULL);
						if (clientSocket != -1)
							pmonitoring.monitor(clientSocket,
												POLLIN | POLLOUT| POLLHUP | 
												POLLRDHUP, EventHandler::CLIENT);
						std::cout << "New socket connection" << std::endl;
						std::cout << pmonitoring.getClientsConnected() 
						  		  << " clients connected." << std::endl; 
					}
					break;
				}
				case EventHandler::CLIENT:
				{
					if (it->events & POLLIN)
					{
						static_cast<ClientData *>(data)->getRequest().
							readReceived(data->getFd(), serverSocket);
							break;
					}
					else if (it->events & POLLOUT)
					{
						if (static_cast<ClientData *>(data)->getRequest().isBadRequest())
						{
							send(data->getFd(), "Bad Request\n", 13, 0);
							close(data->getFd());
							pmonitoring.unmonitor(data->getFd());
							std::cout << "Bad Request: Socket closed"<< std::endl;
							std::cout << pmonitoring.getClientsConnected() 
						  			  << " clients connected." << std::endl; 
						}
					}
					break;
				}
				default:
					break;
			}
		}
		// std::cout << pFds.size();
	}
	/*sockaddr_in clientAddr;
	socklen_t len;
	int clientSocket = accept(serverSocket,
		(struct sockaddr*)&clientAddr, &len);
	//char buffer[1024] = {0};
	if (clientSocket > -1)
	{

		//char buffer[1024] = {0};
		//recv(clientSocket, buffer, sizeof(buffer), 0);
		//std::cout << "Message from client: " << buffer << std::endl;
		HttpRequest::decode(clientSocket, serverSocket);
		send(clientSocket, "message", 7, 0);
		//close(clientSocket);
	}
}*/
	return (0);
}