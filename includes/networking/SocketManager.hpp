/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:25:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:37:37 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETMANAGER_HPP
# define SOCKETMANAGER_HPP

# include "./../lib.hpp"
# include "./../networking/Socket.hpp"
# include "./../events/EventMonitoring.hpp"

class	SocketManager
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