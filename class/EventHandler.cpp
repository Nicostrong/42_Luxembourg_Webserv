/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 14:54:03 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/EventHandler.hpp"
#include "../includes/ClientData.hpp"

template <typename T>
EventHandler<T>::EventHandler(int fd, EventsHooks<T> &hooks) 
	: _fd(fd), _hooks(hooks) {}

template <typename T>
EventHandler<T>::EventHandler(const EventHandler &obj) : _fd(obj._fd), 
	_hooks(obj._hooks) {}

template <typename T>
EventHandler<T>::~EventHandler() {}

template <typename T>
EventHandler<T> &EventHandler<T>::operator=(const EventHandler<T> &obj)
{
	if (this != &obj)
		this->_hooks = obj._hooks;
	return (*this);
}

template <typename T>
int EventHandler<T>::getFd() const
{
	return (this->_fd);
}

//Events

template <typename T>
void	EventHandler<T>::onRead() const
{
	if (this->_hooks.context && this->_hooks.onRead)
		this->_hooks.context->*this->_hooks.onRead(this->_fd);
}

template <typename T>
void	EventHandler<T>::onWrite() const
{
	if (this->_hooks.context && this->_hooks.onWrite)
		this->_hooks.context->*this->_hooks->onWrite(this->_fd);
}

template <typename T>
void	EventHandler<T>::onClose() const
{
	if (this->_hooks.context && this->_hooks.onClose)
		this->_hooks.context->*this->_hooks.onClose(this->_fd);
}

/*EventHandler *EventHandler::getHerited(int fd, EventsHooks &hooks)
{
	switch (type)
	{
		case CLIENT:
			return (new ClientData(fd, hooks));
		
		default:
			return (new EventHandler(fd, type, hooks));
	}
}*/

