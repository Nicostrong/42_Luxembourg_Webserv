/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:52:16 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/22 10:46:18 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include "../includes/HttpRequest.hpp"
#include "../includes/PollMonitoring.hpp"
#include "../includes/ClientData.hpp"

#define MAX_CONNECTIONS 20

int main()
{
	PollMonitoring pmonitoring;
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

	pmonitoring.monitor(serverSocket, POLLIN, BaseData::SERVER);
	std::cout << "Listening on port 8080" << std::endl;

	while (pmonitoring.updatePoll() != -1)
	{
		const std::vector<pollfd> pFds = pmonitoring.getFds();
		std::vector<BaseData *> pFdsData = pmonitoring.getFdsData();

		for (size_t i = 0; i < pFds.size(); i++)
		{
			if (pFds.at(i).revents & (POLLERR | POLLHUP | POLLRDHUP))
			{
				close(pFds.at(i).fd);
				pmonitoring.unmonitor(pFds.at(i).fd);
				std::cout << "Socket closed by remote" << std::endl;
				std::cout << pmonitoring.getClientsConnected() 
						  << " clients connected." << std::endl; 
				continue;
			}
			switch (pFdsData.at(i)->getType())
			{
				case BaseData::SERVER:
				{
					if (pFds.at(i).revents & POLLIN)
					{
						int clientSocket = accept(serverSocket, NULL, NULL);
						if (clientSocket != -1)
							pmonitoring.monitor(clientSocket,
												POLLIN | POLLOUT| POLLHUP | 
												POLLRDHUP, BaseData::CLIENT);
						std::cout << "New socket connection" << std::endl;
						std::cout << pmonitoring.getClientsConnected() 
						  		  << " clients connected." << std::endl; 
					}
					break;
				}
				case BaseData::CLIENT:
				{
					if (pFds.at(i).revents & POLLIN)
					{
						static_cast<ClientData *>(pFdsData.at(i))->getRequest().
							readReceived(pFds.at(i).fd, serverSocket);
							break;
					}
					else if (pFds.at(i).revents & POLLOUT)
					{
						if (static_cast<ClientData *>(pFdsData.at(i))->getRequest().isBadRequest())
						{
							send(pFds.at(i).fd, "Bad Request\n", 13, 0);
							close(pFds.at(i).fd);
							pmonitoring.unmonitor(pFds.at(i).fd);
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