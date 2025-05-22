/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MemoryPool.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:18:30 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/22 18:54:54 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/MemoryPool.hpp"

MemoryPool::MemoryPool() 
{
	this->_smallBuffers.reserve(MAX_CLIENT);
	this->_bigBuffers.reserve(DHEAD_BIG_BUFF_N);;
}

MemoryPool::MemoryPool(const MemoryPool& obj) : 
	_smallBuffers(obj._smallBuffers), _bigBuffers(obj._bigBuffers), _smallAvailables(obj._smallAvailables), _bigAvailables(obj._bigAvailables) {}

MemoryPool::~MemoryPool() {}

MemoryPool MemoryPool::operator=(const MemoryPool& obj)
{
	if (this != &obj)
	{
		this->_bigBuffers = obj._bigBuffers;
		this->_smallBuffers = obj._smallBuffers;
	}
	return (*this);
}

void 