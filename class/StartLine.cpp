/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartLine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:10:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 11:36:13 by fdehan           ###   ########.fr       */
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
	_state(RECEIVING), _startLineEnd(0) 
{
	this->_map.reserve(3);
}

StartLine::~StartLine() {}

StartLine& StartLine::operator=(const StartLine& obj)
{
	(void)obj;
	return (*this);
}

StartLine::State StartLine::getState() const
{
	return (this->_state);
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
		this->_startLineEnd = pos;
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
		canBeValidUri(this->_map.at(1));
		canBeValidHttpVersion(this->_map.at(2));
	}

	if (this->_buff->isBufferFull() && this->_state == RECEIVING)
	{
		this->_state = TOO_LARGE;
		return ;
	}
}

void StartLine::canBeValidMethod(const t_string& str)
{
	if (this->_state != RECEIVING)
		return ;
		
	if (str.len == 0 )
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

void StartLine::canBeValidUri(const t_string& path)
{
	if (this->_state != RECEIVING)
		return ;
		
	if (path.len == 0 || this->_buff->at(path.pos) != '/' ||
		this->_buff->find("//", path.pos, path.len) != std::string::npos)
	{
		this->_state = MALFORMED;
		return ;
	}
}

void StartLine::canBeValidHttpVersion(const t_string& ver)
{
	if (this->_state != RECEIVING)
		return ;
		
	if (ver.len != 8 || !this->_buff->startWith("HTTP/", ver.pos, ver.len) || 
		!std::isdigit(this->_buff->at(ver.pos + 5)) || 
		this->_buff->at(ver.pos + 6) != '.' || 
		!std::isdigit(this->_buff->at(ver.pos + 7)))
	{
		this->_state = MALFORMED;
		return ;
	}
}

//Helpers

void StartLine::allocateBuff()
{
	if (!this->_buff)
		this->_buff = this->_mPool.getSmallBufferFromPool();
}