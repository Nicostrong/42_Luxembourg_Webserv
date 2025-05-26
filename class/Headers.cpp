/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:43:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 11:37:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Headers.hpp"
#include "./includes/Socket.hpp"

Headers::Headers(MemoryPool& mPool) : _mPool(mPool), _buff(NULL), _headersEnd(0), _state(RECEIVING) {}

Headers::Headers(const Headers& obj) : _mPool(obj._mPool), _buff(NULL), _headersEnd(0), _state(RECEIVING) {}

Headers::~Headers() 
{
    if (this->_buff)
        this->_mPool.setAvailableBuffer(this->_buff);
}

Headers& Headers::operator=(const Headers& obj)
{
    (void)obj;
    return (*this);
}

Headers::State Headers::getState() const
{
    return (this->_state);
}

void    Headers::readBufferLeft(Buffer& buff, size_t pos)
{
    allocateBuff();
    this->_buff->copyFrom(buff, pos);
}

void    Headers::read(int socket)
{
    allocateBuff();
    if (!this->_buff)
        return ;
    
    size_t bytes = recv(socket, this->_buff->getDataUnused(), 
        std::max((size_t)HEAD_MAX_READ, this->_buff->getBufferUnused()), 0);
    if (bytes == -1)
        throw Socket::SocketReadException();
}

Buffer* Headers::getBuffer()
{
    return (this->_buff);
}

void Headers::parseHeaders()
{
	size_t sPos = 0;
	size_t ePos = this->_buff->find(CRLF);

	while (ePos != std::string::npos)
	{
		parseHeader(sPos, ePos - 1);
		sPos = ePos + 2;
		ePos = this->_buff->find(CRLF, sPos);
	}

    if (this->_state == RECEIVING && this->_buff->isBufferFull())
    {
        this->_state = TOO_LARGE;
        return ;
    }
	/*if (this->_headers.find("HOST") == this->_headers.end())
	{
		this->_state = HTTP_INVALID;
		return ;
	}*/
}

void Headers::parseHeader(size_t start, size_t end)
{
    size_t length = end - start;

    if (length == 0)
    {
        this->_headersEnd = start + 2;
        this->_state = READY;
        return ;
    }

	size_t sep = this->_buff->find(':', start, length);
    
	if (sep == std::string::npos || sep == start)
	{
		this->_state = MALFORMED;
		return ;
	}

	int	folding = (length - sep > 1) ? 
				  this->_buff->at(sep + 1) == ' ' || this->_buff->at(sep + 1) == '\t' : 0;

	if (!isHeaderNameValid(start, sep - 1))
	{
		this->_state = MALFORMED;
		return ;
	}
	normalizeHeaderName(start, sep - 1);

	this->_mapKeys.push_back({start, sep - start - 1});
    this->_mapValues.push_back({sep + 1, end - sep});
}

void Headers::allocateBuff()
{
    Buffer* temp = NULL;
    if (!this->_buff)
        this->_buff = this->_mPool.getSmallBufferFromPool();
    else if (this->_buff->isBufferFull())
    {
        temp = this->_mPool.getMediumBufferFromPool();
        if (temp)
        {
            temp->copyFrom(*this->_buff);
            this->_buff = temp;
        }
    }
}

bool Headers::isHeaderNameValid(size_t nStart, size_t nEnd)
{
	while (nStart != nEnd) 
	{
        char c = this->_buff->at(nStart);
		if (!std::isalnum(c) && c != '-' && c != '_' )
			return (false);
        ++nStart;
	}
	return (true);
}

void Headers::normalizeHeaderName(size_t nStart, size_t nEnd)
{
    while (nStart != nEnd) 
	{
        this->_buff->at(nStart) = std::toupper(this->_buff->at(nStart));
        ++nStart;
	}
}

bool Headers::isHeaderPresent(const std::string& name) const
{
    return (getHeaderIndex(name) != std::string::npos);
}

const t_string* Headers::getHeaderValue(const std::string& name) const
{
    size_t headerPos = getHeaderIndex(name);

    if (headerPos == std::string::npos)
        return (NULL);
    return (&this->_mapValues.at(headerPos));
}

size_t Headers::getHeaderIndex(const std::string& name) const
{
    for (int i = 0; i < this->_mapKeys.size(); ++i)
    {
        t_string key = this->_mapKeys.at(i);
        
        if (key.len == name.size() && std::strncmp(
            this->_buff->getData() + key.pos, name.c_str(),key.len) == 0)
            return (i);
    }
    return (std::string::npos);
}