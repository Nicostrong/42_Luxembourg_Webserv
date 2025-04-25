/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/25 14:44:49 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/EventHandler.hpp"
#include "../includes/ClientData.hpp"

EventHandler::EventHandler(int fd, BaseDataType type) : _fd(fd), _type(type) {}

EventHandler::EventHandler(const EventHandler &obj) : _fd(obj._fd),  _type(obj._type) {}

EventHandler::~EventHandler() {}
		
EventHandler &EventHandler::operator=(const EventHandler &obj)
{
	(void)obj;
	return (*this);
}

int EventHandler::getFd() const
{
	return (this->_fd);
}

EventHandler::BaseDataType EventHandler::getType() const
{
	return (this->_type);
}

EventHandler *EventHandler::getHerited(int fd, BaseDataType type)
{
	switch (type)
	{
		case CLIENT:
			return (new ClientData(fd));
		
		default:
			return (new EventHandler(fd, type));
	}
}

