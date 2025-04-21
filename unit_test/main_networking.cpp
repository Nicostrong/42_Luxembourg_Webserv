/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:52:16 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 16:03:37 by fdehan           ###   ########.fr       */
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

#define MAX_CONNECTIONS 20

int main()
{
	PollMonitoring pmonitoring;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	//std::vector<pollfd> fds(MAX_CONNECTIONS);

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Socket failed to be created" << std::endl;
		return (1);
	}

	if (bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "Socket faield to start listening" << std::endl;
		return (1);
	}
	if (listen(serverSocket, 5) == -1)
	{
		std::cerr << "Socket faield to start listening" << std::endl;
		return (1);
	}

	pmonitoring.monitor(serverSocket, POLLIN);
	std::cout << "Listening on port 8080" << std::endl;
	
	while (pmonitoring.updatePoll() != -1)
	{
		const std::vector<pollfd> pFds = pmonitoring.getFds();
		std::vector<pollfd>::const_iterator it;
		for (it = pFds.begin(); it != pFds.end(); ++it) {
			if(it->revents & POLLIN) 
			{
				if (it == pFds.begin())
				{
					int clientSocket = accept(serverSocket, NULL, NULL);
					if (clientSocket != -1)
						pmonitoring.monitor(clientSocket, POLLIN | POLLHUP | POLLRDHUP);
					std::cout << "New socket connection" << std::endl;
				}
			}
			if(it->revents & (POLLERR | POLLHUP | POLLRDHUP)) 
			{
				std::cout << "Socket closed by remote" << std::endl;
				close(it->fd);
				pmonitoring.unmonitor(it->fd);
			}
		}
		//std::cout << pFds.size();
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