/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerListener.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:39:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 17:42:09 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ServerListener.hpp"

ServerListener::ServerListener(size_t port) : _port(port) {}

ServerListener::ServerListener(const ServerListener& obj) : _port(obj._port) {}

ServerListener::~ServerListener() {}

ServerListener& ServerListener::operator=(const ServerListener& obj)
{
    if (this != &obj)
    {
        this->_port = obj._port;
    }
    return (*this);
}

