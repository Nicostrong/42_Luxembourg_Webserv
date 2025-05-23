/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:43:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/23 10:57:55 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Headers.hpp"
#include "./includes/Socket.hpp"

Headers::Headers(MemoryPool& mPool) : _mPool(mPool), _buff(NULL), _headersEnd(0), _state(RECEIVING) {}

Headers::Headers(const Headers& obj) : _mPool(obj._mPool), _buff(NULL), _headersEnd(0), _state(RECEIVING) {}

Headers::~Headers() 
{
    if (_buff)
        this->_mPool.setAvailableBuffer(this->_buff);
}

Headers& Headers::operator=(const Headers& obj)
{
    return (*this);
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

void Headers::isHeadersReceived()
{
    std::vector<char> buff = this->_buff->getVector();
    size_t pos = this->_buff->getBufferRead();
    size_t length = 0;
    while (pos < this->_buff->getBufferUsed())
    {
        if (buff.at(pos) == CRLF)
        
        ++pos;
    }
}

void Headers::allocateBuff()
{
    Buffer* temp = NULL;
    if (!this->_buff)
        temp = this->_mPool.getSmallBufferFromPool();
    else if (this->_buff->isBufferFull())
    {
        temp = this->_mPool.getMediumBufferFromPool();
        if (temp)
            temp->copyFrom(*this->_buff);
    }
    this->_buff = temp;
}
