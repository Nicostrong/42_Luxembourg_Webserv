/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Endpoint.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:52:43 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:36:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/Endpoint.hpp"

Endpoint::Endpoint(const Ip& ip, size_t port) : _ip(ip), _port(port) {}

Endpoint::Endpoint(const Endpoint& obj) :_ip(obj._ip), _port(obj._port) {}

Endpoint::~Endpoint() {}

Endpoint& Endpoint::operator=(const Endpoint& obj)
{
    if (this != &obj)
    {
        this->_ip = obj._ip;
        this->_port = obj._port;
    }
    return (*this);
}

const Ip& Endpoint::getIp() const
{
    return (this->_ip);
}

size_t Endpoint::getPort() const
{
    return (this->_port);
}

Endpoint Endpoint::getEntryAddress(int fd)
{
    struct sockaddr_in	entryAddr;
	socklen_t addrLen = sizeof(entryAddr);

    if (fd < 2)
        throw std::runtime_error("Invalid socket");
    
    if (getsockname(fd, (struct sockaddr*)&entryAddr, &addrLen) == -1)
        throw std::runtime_error("Invalid socket");

    return (Endpoint(Ip(entryAddr.sin_addr.s_addr), htons(entryAddr.sin_port)));
}

Endpoint Endpoint::getEndpoint(sockaddr_in endpoint)
{
    return (Endpoint(Ip(endpoint.sin_addr.s_addr), htons(endpoint.sin_port)));
}