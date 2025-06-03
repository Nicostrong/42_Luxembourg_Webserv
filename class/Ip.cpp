/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ip.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:49:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 17:42:09 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/Ip.hpp"

Ip::Ip(const in_addr_t ipv4)
{
    
}

Ip::Ip(const std::string& ipv4)
{
    
}

Ip::Ip(const Ip& obj) 
{
    (void)obj;
}

Ip::~Ip() {}

Ip& Ip::operator=(const Ip& obj) 
{
    if (this != &obj)
    {}
    return (*this);
}

in_addr_t Ip::ipv4StringToBytes(const std::string& ip)
{
    if (ip.size() > 15)
        return (0);
    
    std::stringstream ss;
    std::vector<std::string> arr;

    arr.reserve(4);
    for ()
}