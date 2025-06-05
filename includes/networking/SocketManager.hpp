/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:29:00 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETMANAGER_HPP
# define SOCKETMANAGER_HPP

#include "./../lib.hpp"
#include "./../events/EventMonitoring.hpp"
#include "./../networking/Socket.hpp"

class SocketManager
{
	public:
		SocketManager();
		~SocketManager();

		void	add(Socket& sock, EventMonitoring& em);
		void	remove(Socket& sock, EventMonitoring& em);
	private:
		SocketManager(const SocketManager& obj);
		SocketManager& operator=(const SocketManager& obj);

		std::vector<Socket*> _sockets;
};

#endif