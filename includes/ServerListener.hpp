/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:40:47 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 16:44:07 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERLISTENER_HPP
#define SERVERLISTENER_HPP

#include "lib.hpp"

class ServerListener
{
    public:
        ServerListener(size_t port);
        ServerListener(const ServerListener& obj);
        ~ServerListener();
        ServerListener& operator=(const ServerListener& obj);
    private:
        size_t _port;
};

#endif