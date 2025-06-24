/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ip.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:49:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/23 10:57:57 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/Ip.hpp"

Ip::Ip(const in_addr_t ipv4)
{
    this->_ipBytes = ipv4;
    this->_ipString = ipv4BytesToString(ipv4);
}

Ip::Ip(const std::string& ipv4)
{
    this->_ipBytes = ipv4StringToBytes(ipv4);
    this->_ipString = ipv4;
}

Ip::Ip(const Ip& obj) : _ipBytes(obj._ipBytes), _ipString(obj._ipString) {}

Ip::~Ip() {}

Ip& Ip::operator=(const Ip& obj) 
{
    if (this != &obj)
    {
        this->_ipBytes = obj._ipBytes;
        this->_ipString = obj._ipString;
    }
    return (*this);
}

in_addr_t Ip::getIpBytes() const
{
    return (this->_ipBytes);
}

const std::string& Ip::getIpString() const
{
    return (this->_ipString);
}

in_addr_t Ip::ipv4StringToBytes(const std::string& ip)
{
    if (ip.size() > 15)
        throw std::runtime_error("Invalid IP");
    
    in_addr_t ipBytes = 0;
    uint8_t i = 1;
    size_t prevPos = 0;
    size_t pos = ip.find('.');
    std::string token;
    
    while (pos != std::string::npos)
    {
        if (i >= 4)
            throw std::runtime_error("Invalid IP");

        token = ip.substr(prevPos, pos - prevPos);
        ipBytes |= getOctetDecimalValue(token) << (32 - 8 * i);
        prevPos = pos + 1;
        pos = ip.find('.', prevPos);
        ++i;
    }
    
    token = ip.substr(prevPos);
    ipBytes |= getOctetDecimalValue(token) >> (32 - 8 * i);
    
    if (i < 4)
        throw std::runtime_error("Invalid IP");
    
    return (htonl(ipBytes));
}

std::string Ip::ipv4BytesToString(in_addr_t ip)
{
    
    std::stringstream ss;
   
    ip = htonl(ip);
    ss << ((ip >> 24) & 0xFF) << "." 
       << ((ip >> 16) & 0xFF) << "." 
       << ((ip >> 8) & 0xFF) << "." 
       << (ip & 0xFF);
    
    return (ss.str());
}

//Helpers

bool    Ip::isDigits(const std::string& str)
{
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

size_t  Ip::getOctetDecimalValue(const std::string& o)
{ 
    if (o.size() > 3 || o.size() < 1 || !isDigits(o))
        throw std::runtime_error("Invalid IP");

    size_t result;
    std::stringstream ss(o);
    ss >> result;

    if (ss.fail() || result > 255)
        throw std::runtime_error("Invalid IP");

    return (result);
}

bool				Ip::operator<(const Ip& other) const
{
    return (this->_ipBytes < other._ipBytes);
}