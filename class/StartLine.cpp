/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:10:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/24 10:10:23 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/StartLine.hpp"
#include "./../includes/Socket.hpp"

StartLine::StartLine(MemoryPool& mPool) : _mPool(mPool), _state(RECEIVING), 
	_startLineEnd(0) 
{
	this->_map.reserve(3);
}

StartLine::StartLine(const StartLine& obj) : _mPool(obj._mPool), 
	_state(obj._state), _startLineEnd(0) 
{
	this->_map.reserve(3);
}

StartLine::~StartLine() {}

StartLine& StartLine::operator=(const StartLine& obj)
{
	(void)obj;
	return (*this);
}

void StartLine::read(int socket)
{
    allocateBuff();
    if (!this->_buff)
        return ;
    
    size_t bytes = recv(socket, this->_buff->getDataUnused(), 
        std::max((size_t)START_LINE_READ, this->_buff->getBufferUnused()), 0);
    if (bytes == -1)
        throw Socket::SocketReadException();
}

void StartLine::parseStartLine()
{
	size_t pos = this->_buff->find(CRLF);
	size_t sPos = 0;
	size_t i = 0;

	if (pos)
	{
		for (size_t j = 0; j < this->_map.capacity(); ++j)
		{
			while (i < this->_buff->getBufferUnread() && 
					this->_buff->at(i) != ' ')
				i++;
			this->_map.push_back({sPos, i - sPos});
			i++;
			sPos = i;
		}

		if (i != pos || this->_map.size() < this->_map.capacity())
		{
			this->_state = MALFORMED;
			return ;
		}
		canBeValidMethod(this->_map.at(0));
	}

	if (this->_buff->isBufferFull() && this->_state == RECEIVING)
	{
		this->_state = TOO_LARGE;
		return ;
	}
}

void StartLine::canBeValidMethod(const t_string& str)
{
	if (str.len == 0)
	{
		this->_state = MALFORMED;
		return ;
	}

	for (int i = str.pos; i < str.pos + str.len; ++i)
	{
		if (!std::isupper(this->_buff->at(i)))
		{
			this->_state = MALFORMED;
			return ;
		}
	}
}

//Helpers

void StartLine::allocateBuff()
{
	if (!this->_buff)
		this->_buff = this->_mPool.getSmallBufferFromPool();
}