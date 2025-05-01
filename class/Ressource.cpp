/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:51:46 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 13:20:41 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Ressource.hpp"

Ressource::Ressource(const std::string& loc, EventMonitoring& em) : _loc(loc), 
	_em(em), _state(WAITING) 
{
	this->_fd = open(loc.c_str(), O_WRONLY);
	if (this->_fd == -1)
		this->_state = ERROR;
	else
		this->_em.monitor(this->_fd, POLLIN, 0, *this);
}

Ressource::Ressource(const Ressource& obj) : _loc(obj._loc), _em(obj._em), 
	_state(obj._state), _raw(obj._raw) 
{
	if (obj._fd != -1)
	{
		this->_fd = dup(obj._fd);
		if (this->_fd == -1)
			this->_state = ERROR;
		else
			this->_em.monitor(this->_fd, POLLIN, 0, *this);
	}
}

Ressource::~Ressource() 
{
	if (this->_fd != -1)
	{
		close(this->_fd);
		this->_em.unmonitor(this->_fd);
	}
}

Ressource& Ressource::operator=(const Ressource& obj)
{
	(void)obj;
	return (*this);
}

const std::string&	Ressource::getLoc() const
{
	return (this->_loc);
}

Ressource::State Ressource::getState() const
{
	return (this->_state);
}

const std::string& Ressource::getRaw() const
{
	return (this->_raw);
}

void Ressource::onReadEvent(int fd, int type, EventMonitoring& em)
{
	ssize_t bytes;
	std::vector<char> buff(RESSOURCE_BUFFER_SIZE);

	while ((bytes = read(fd, buff.data(), RESSOURCE_BUFFER_SIZE)) == 
		RESSOURCE_BUFFER_SIZE)
		this->_raw.append(buff.data(), bytes);
	close(fd);
	this->_fd = -1;
	
	if (bytes == -1)
	{
		this->_state = ERROR;
		return ;
	}	
	
	this->_raw.append(buff.data(), bytes);
	this->_state = RECEIVED;
	em.unmonitor(fd);
	(void)type;
}

void Ressource::onWriteEvent(int fd, int type, EventMonitoring& em)
{
	(void)fd;
	(void)type;
	(void)em;
}

void Ressource::onCloseEvent(int fd, int type, EventMonitoring& em)
{
	(void)fd;
	(void)type;
	(void)em;
}