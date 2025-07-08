/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:27:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:49:48 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/networking/Chunk.hpp"

Chunk::Chunk() : _bytesReceived(0), _chunkSize(0), _chunksReceived(0), _bodySize(0), _bodyLimit(0), _state(CHUNK_START) {}

Chunk::Chunk(size_t limit) : _bytesReceived(0), _chunkSize(0), _chunksReceived(0), _bodySize(0), _bodyLimit(limit), _state(CHUNK_START) {}

Chunk::Chunk(const Chunk& obj) : _bytesReceived(obj._bytesReceived), _chunkSize(obj._chunkSize), _chunksReceived(obj._chunksReceived), 
	_bodySize(obj._bodySize), _bodyLimit(obj._bodyLimit), _state(obj._state) {}

Chunk::~Chunk() {}

Chunk& Chunk::operator=(const Chunk& obj)
{
	if (this != &obj)
	{
		this->_bytesReceived = obj._bytesReceived;
		this->_chunkSize = obj._chunkSize;
		this->_chunksReceived = obj._chunksReceived;
		this->_bodySize = obj._bodySize;
		this->_bodyLimit = obj._bodyLimit;
		this->_state = obj._state;
	}
	return (*this);
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
			handleChunkStart();
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

void Chunk::handleChunkStart()
{
	this->_chunksReceived++;
	if (this->_chunksReceived > MAX_CHUNKS)
		throw HttpSevereExceptions(HttpBase::CONTENT_TOO_LARGE);
	this->_state = CHUNK_HEAD;
}


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

	this->_chunkSize = convertHexa(
		std::string(buff.getDataUnread(), std::min(pos, buff.find(';'))));
	
	if (this->_chunkSize > MAX_CHUNK_SIZE)
		throw HttpSevereExceptions(HttpBase::CONTENT_TOO_LARGE);
	
	LOG_DEB(this->_chunkSize);
	this->_bodySize += this->_chunkSize;
	
	if (this->_bodyLimit && this->_bodySize > this->_bodyLimit)
		throw HttpSevereExceptions(HttpBase::CONTENT_TOO_LARGE);
	buff.setBufferRead(pos - buff.getBufferRead() + 2);
	this->_state = CHUNK_DATA;
}

size_t Chunk::handleChunkData(Buffer& buff)
{
	if (this->_bytesReceived == this->_chunkSize)
	{
		buff.alignData();
		if (buff.getBufferUnread() < 2)
			return (0);

		if (buff.find(CRLF) != 0)
			throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
		
		buff.setBufferRead(2);
		this->_bytesReceived = 0;
		this->_state = CHUNK_START;
		if (!this->_chunkSize)
			this->_state = CHUNK_END;
		return (0);
	}

	size_t len = std::min(buff.getBufferUnread(), this->_chunkSize - this->_bytesReceived);
	
	this->_bytesReceived += len;
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
