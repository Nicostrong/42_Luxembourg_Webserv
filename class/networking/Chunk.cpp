/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:27:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/05 09:07:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/networking/Chunk.hpp"

Chunk::Chunk() : _received(0), _len(0), _state(CHUNK_HEAD) {}

Chunk::Chunk(size_t len) : _received(0), _len(len), _state(CHUNK_HEAD) {}

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

Chunk::State Chunk::getState() const
{
	return (this->_state);
}

size_t Chunk::handleChunk(Buffer& buff)
{
	switch (this->_state)
	{
		case CHUNK_START:
			this->_state = CHUNK_HEAD;
		// fallthrough
		case CHUNK_HEAD:
			handleChunkHead(buff);
			if (this->_state == CHUNK_HEAD)
				return (0);
		// fallthrough
		case CHUNK_DATA:
			return (handleChunkData(buff));
		default:
			return (0);
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
			throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
		return ;
	}

	if (!isHexaValid(std::string(buff.getDataUnread(), std::min(pos, buff.find(';')))))
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	this->_len = convertHexa(
		std::string(buff.getDataUnread(), std::min(pos, buff.find(';'))));
	LOG_DEB(this->_len);
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
			throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
		
		buff.setBufferRead(2);
		this->_received = 0;
		this->_state = CHUNK_START;
		if (!this->_len)
			this->_state = CHUNK_END;
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
        throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
    return (res);
}

bool Chunk::isHexaValid(const std::string& hex)
{
	if (hex.size() > sizeof(size_t) * 2 || hex.empty() || 
		hex.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos)
		return (false);
	return (true);
}
