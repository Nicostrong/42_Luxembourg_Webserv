/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_ev.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:37:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/04 15:14:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Server.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

/*void		Server::onSocketClosedEvent( const Socket& s )
{
	this->_em.unmonitor(s.getSocket());
	close(s.getSocket());
	this->_lSockets.remove(s);
	std::cout << "A client has disconnected" << std::endl;
	return ;
}*/