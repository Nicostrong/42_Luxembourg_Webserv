/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:27:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 20:52:54 by fdehan           ###   ########.fr       */
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
	if (!buff.getBufferUnread())
		return (0);

	switch (this->_state)
	{
		case CHUNK_HEAD:
			handleChunkHead(buff);
		// fallthrough
		case CHUNK_DATA:
			return (handleChunkData(buff));	
	}
	return (0);
}

//Helpers

void Chunk::handleChunkHead(Buffer& buff)
{
	buff.alignData();
	
	size_t pos = buff.find(CRLF);

	if (pos == std::string::npos)
	{
		if (buff.isBufferFull())
			throw std::runtime_error("Malformed chunk");
		return ;
	}

	this->_len = convertHexa(
		std::string(buff.getDataUnread(), std::min(pos, buff.find(';'))));
	
	buff.setBufferRead(pos - buff.getBufferRead() + 2);
	this->_state = CHUNK_DATA;
}

size_t Chunk::handleChunkData(Buffer& buff)
{
	if (this->_received == this->_len)
	{
		buff.alignData();
		if (buff.getBufferUnread() < 2)
			return (0);

		if (buff.find(CRLF) != 0)
			throw std::runtime_error("Malformed chunk");
		
		buff.setBufferRead(2);
		this->_received = 0;
		this->_state = CHUNK_HEAD;
		return (0);
	}

	size_t len = std::min(buff.getBufferUnread(), this->_len - this->_received);
	
	this->_received += len;
	return (len);
}

size_t Chunk::convertHexa(const std::string& str)
{
    std::istringstream iss(str);
    size_t res;

    iss >> std::hex >> res;
    if (iss.fail()) 
        throw std::runtime_error("Malformed chunk");
    return (res);
}
