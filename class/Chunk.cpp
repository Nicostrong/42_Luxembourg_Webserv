/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:27:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 17:02:11 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Chunk.hpp"

Chunk::Chunk() : _received(0), _len(0) {}

Chunk::Chunk(size_t len) : _received(0), _len(len) {}

Chunk::Chunk(const Chunk& obj)
{
    this->_received = obj._received;
    this->_len = obj._len;
}
Chunk::~Chunk() {}

Chunk& Chunk::operator=(const Chunk& obj)
{
	if (this != &obj)
	{
		this->_received = obj._received;
		this->_len = obj._len;
	}
	return (*this);
}

void Chunk::setReceived(size_t received)
{
	size_t tReceived = this->_received + received;

	if (tReceived - received != this->_received || this->_received > this->_len)
		this->_received = this->_len;
	else
		this->_received = tReceived;
}

size_t Chunk::getReceived() const
{
	return (this->_received);
}

size_t Chunk::getLen() const
{
	return (this->_len);
}

size_t Chunk::handleChunk(Buffer& buff)
{
	if (buff.getBufferUnread() < 1)
		return (0);

	switch (this->_state)
	{
		case 
	}
}