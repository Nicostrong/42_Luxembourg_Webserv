/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:52:16 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/18 16:17:46 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main()
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	
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
	std::cout << "Listening on port 8080" << std::endl;
	while (1)
	{
		sockaddr_in clientAddr;
		socklen_t len;
		int clientSocket = accept(serverSocket, 
			(struct sockaddr*)&clientAddr, &len);
		char buffer[1024] = {0};
		if (clientSocket > -1)
		{
			char buffer[1024] = {0};
			recv(clientSocket, buffer, sizeof(buffer), 0);
			std::cout << "Message from client: " << buffer << std::endl;
			send(clientSocket, "message", 7, 0);
			close(clientSocket);
		}
	}
	return (0);
}