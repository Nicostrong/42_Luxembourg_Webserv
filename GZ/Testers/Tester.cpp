/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:13:56 by gzenner           #+#    #+#             */
/*   Updated: 2025/07/01 11:32:19 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cerr<<"Socket creation failed\n";
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
        std::cerr<<"Invalid address/Address not supported\n";

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        std::cerr<<"Connection failed\n";

    std::string msg;
    msg += "GET /api/users/123 HTTP/1.1";
    msg += "Host: example.com";
    msg += "Accept: application/json";
    
    ssize_t sent = send(sockfd, msg.c_str(), msg.size(), 0);
    if (sent < 0)
        std::cerr<<"Send failed\n";
    
    char buffer[1024];
    /*ssize_t received = recv(sockfd, buffer, 1024 - 1, 0);
    if (received < 0)
        std::cerr<<"Receive error\n";
    //if (received == 0) break;
    buffer[received] = 0;*/

    //std::cout<<buffer<<"\n";
        
    std::cout << "Hello from Tester.\n";
    return (0);
}