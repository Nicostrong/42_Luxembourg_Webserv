/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:51:46 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/30 18:04:02 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Ressource.hpp"

Ressource::Ressource(int fd) : _fd(fd) {}

Ressource::Ressource(const Ressource& obj)
{
	return ;
}

Ressource::~Ressource() {}

Ressource& Ressource::operator=(const Ressource& obj)
{
	return (*this);
}

Ressource::State Ressource::getState() const
{
	return (this->_state);
}

const std::string& Ressource::getRaw() const
{
	return (this->_raw);
}

void Ressource::onReadEvent(int fd, int type)
{
	(void)fd;
	(void)type;
}

void Ressource::onWriteEvent(int fd, int type)
{
	(void)fd;
	(void)type;
}

void Ressource::onCloseEvent(int fd, int type)
{
	(void)fd;
	(void)type;
}