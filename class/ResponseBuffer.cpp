/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuffer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:14:18 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 15:55:00 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseBuffer.hpp"
#include "../includes/Socket.hpp"

ResponseBuffer::ResponseBuffer(Socket& ctx) : _ctx(&ctx), _buff(RESPONSE_BUFFER_SIZE), _pos(0), _flushCount(0) 
{}

ResponseBuffer::ResponseBuffer(const ResponseBuffer& obj) : _ctx(obj._ctx),
    _buff(obj._buff), _pos(obj._pos), _flushCount(obj._flushCount) {}

ResponseBuffer::ResponseBuffer(const ResponseBuffer& obj, Socket& ctx) : 
    _ctx(&ctx), _buff(obj._buff), _pos(obj._pos), _flushCount(obj._flushCount) {}

ResponseBuffer::~ResponseBuffer() {}

ResponseBuffer& ResponseBuffer::operator=(const ResponseBuffer& obj) 
{
    if (this != &obj)
    {
        this->_buff = obj._buff;
        this->_pos = obj._pos;
        this->_ctx = obj._ctx;
        this->_flushCount = obj._flushCount;
    }
    return (*this);
}

size_t ResponseBuffer::getFlushCount() const
{
    return (this->_flushCount);
}

void    ResponseBuffer::bufferize(const std::vector<char>& buff, size_t n)
{
    if (n > RESPONSE_BUFFER_SIZE)
        throw std::runtime_error("Cannot bufferize data is too big");
    if (this->_pos + n > RESPONSE_BUFFER_SIZE)
        flush();
    this->_buff.insert(this->_buff.begin() + this->_pos, buff.begin(), buff.begin() + n);
    this->_pos += n;
}

void    ResponseBuffer::flush()
{
    this->_ctx->queueTxData(this->_buff, this->_pos);
    this->_pos = 0;
    this->_flushCount++;
}

void    ResponseBuffer::clear()
{
    this->_pos = 0;
}

void    ResponseBuffer::reset()
{
    this->_pos = 0;
    this->_flushCount = 0;
}
