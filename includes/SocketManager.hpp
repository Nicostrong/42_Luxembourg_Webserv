/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 10:31:29 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETMANAGER_HPP
# define SOCKETMANAGER_HPP

#include "lib.hpp"
#include "Socket.hpp"
#include "EventMonitoring.hpp"

class SocketManager
{
	public:
		SocketManager();
		~SocketManager();

		void	add(Socket& sock, EventMonitoring& em);
	private:
		SocketManager(const SocketManager& obj);
		SocketManager& operator=(const SocketManager& obj);

		std::vector<Socket*> _sockets;
};

#endif