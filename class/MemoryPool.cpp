/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MemoryPool.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:30 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/24 09:30:15 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/MemoryPool.hpp"

MemoryPool::MemoryPool() 
{
	this->_smallBuffers.reserve(MAX_CLIENT * 2);
	this->_mediumBuffers.reserve(MEDIUM_AMOUNT);
	this->_largeBuffers.reserve(MAX_CLIENT);
}

MemoryPool::MemoryPool(const MemoryPool& obj) : 
	_smallBuffers(obj._smallBuffers), _mediumBuffers(obj._mediumBuffers), 
	_largeBuffers(obj._largeBuffers), _smallAvailables(obj._smallAvailables), 
	_mediumAvailables(obj._mediumAvailables), _largeAvailables(obj._largeAvailables) {}

MemoryPool::~MemoryPool() {}

MemoryPool MemoryPool::operator=(const MemoryPool& obj)
{
	if (this != &obj)
	{
		this->_smallBuffers = obj._smallBuffers;
		this->_smallAvailables = obj._smallAvailables;
		this->_mediumBuffers = obj._mediumBuffers;
		this->_mediumAvailables = obj._mediumAvailables;
		this->_largeBuffers = obj._largeBuffers;
		this->_largeAvailables = obj._largeAvailables;
	}
	return (*this);
}

Buffer* MemoryPool::getSmallBufferFromPool()
{
	return (getBufferFromPool(this->_largeBuffers, this->_largeAvailables, 
		MEDIUM_BUFF));
}

Buffer* MemoryPool::getMediumBufferFromPool()
{
	return (getBufferFromPool(this->_mediumBuffers, this->_mediumAvailables, 
		MEDIUM_BUFF));
}

Buffer*	MemoryPool::getLargeBufferFromPool()
{
	return (getBufferFromPool(this->_largeBuffers, this->_largeAvailables, 
		LARGE_BUFF));
}

Buffer* MemoryPool::getBufferFromPool(std::vector<Buffer*>& buffs, std::queue<Buffer*>& available, size_t buffSize)
{
	Buffer* buff;
	if (available.size() < 1)
	{
		if (buffs.size() >= buffs.capacity())
			throw NoAvailableBuffer();
		buff = new Buffer(buffSize);
		if (!buff)
			throw NoAvailableBuffer();
		buffs.push_back(buff);
		return (buff);
	}
	buff = available.front();
	available.pop();
	return (buff);
}

void MemoryPool::setAvailableBuffer(Buffer* buff)
{
	size_t buffSize = buff->getVector().size();
	
	buff->reset();
	switch (buffSize)
	{
		case SMALL_BUFF:
			this->_smallAvailables.push(buff);
			break;
		case MEDIUM_BUFF:
			this->_mediumAvailables.push(buff);
			break;
		case LARGE_BUFF:
			this->_largeAvailables.push(buff);
			break;
		default:
			throw InvalidBuffer();
	}
}

// Exceptions

const char *MemoryPool::NoAvailableBuffer::what() const throw()
{
	return ("No available buffer");
}

const char *MemoryPool::InvalidBuffer::what() const throw()
{
	return ("Invalid buffer");
}