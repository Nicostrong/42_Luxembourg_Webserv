/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:04:52 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 10:52:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Buffer.hpp"

Buffer::Buffer(size_t bufferSize) : _buffer(bufferSize), 
    _bufferSize(bufferSize), _bufferUsed(0), _bufferRead(0) {}

Buffer::Buffer(const Buffer& obj) : _buffer(obj._buffer), 
    _bufferSize(obj._bufferSize), _bufferUsed(obj._bufferUsed), 
    _bufferRead(obj._bufferRead) {}

Buffer::~Buffer() {}

Buffer& Buffer::operator=(const Buffer& obj)
{
    if (this != &obj)
    {
        this->_buffer = obj._buffer;
        this->_bufferSize = obj._bufferSize;
        this->_bufferUsed = obj._bufferUsed;
        this->_bufferRead = obj._bufferRead;
    }
    return (*this);
}

std::vector<char>&	Buffer::getVector()
{
    return (this->_buffer);
}

char*  Buffer::getData()
{
    return (this->_buffer.data());
}

const char*  Buffer::getData() const
{
    return (this->_buffer.data());
}

char*	Buffer::getDataUnused()
{
    return (this->_buffer.data() + this->_bufferUsed);
}

char*	Buffer::getDataUnread()
{
     return (this->_buffer.data() + this->_bufferRead);
}

size_t Buffer::getBufferUsed()
{
    return (this->_bufferUsed);
}

size_t Buffer::getBufferRead()
{
    return (this->_bufferRead);
}

size_t Buffer::getBufferUnused()
{
    return (this->_bufferSize - this->_bufferUsed);
}

size_t Buffer::getBufferUnread()
{
    return (this->_bufferUsed - this->_bufferRead);
}

void Buffer::setBufferRead(size_t n)
{
	size_t bRead = n + this->_bufferRead;
	
	if (bRead - n != this->_bufferRead || bRead >= this->_bufferUsed)
		this->_bufferUsed = this->_bufferUsed;
	else
		this->_bufferRead = bRead;

}

void Buffer::setBufferUsed(size_t n)
{
	size_t bUsed = n + this->_bufferUsed;
	
	if (bUsed - n != this->_bufferUsed || bUsed >= this->_bufferSize)
		this->_bufferUsed = this->_bufferSize;
	else
		this->_bufferUsed = bUsed;
}

bool Buffer::isBufferFull()
{
	return (this->_bufferUsed == this->_bufferSize);
}

bool Buffer::isBufferRead()
{
	return (this->_bufferRead == this->_bufferUsed);
}

std::vector<char>::iterator	Buffer::beginUnused()
{
	return (this->_buffer.begin() + this->_bufferUsed);
}

std::vector<char>::iterator	Buffer::beginUnread()
{
	return (this->_buffer.begin() + this->_bufferRead);
}

void Buffer::copyFrom(Buffer& buff, size_t pos, size_t n)
{
    if (buff.getVector().size() < this->_buffer.size())
        return ;
    std::copy(buff.getVector().begin() + pos, 
        std::min(pos + n, buff._bufferUsed) + buff.getVector().begin(), 
        this->_buffer.begin());
    setBufferUsed(std::min(pos + n, buff._bufferUsed) - pos);
    setBufferRead(buff.getBufferRead());
}

size_t Buffer::find(const char& c, size_t pos, size_t n)
{
    while (pos < this->_bufferUsed && pos < pos + n)
    {
        if (this->_buffer.at(pos))
            return (pos);
        ++pos;
    }
    return (std::string::npos);
}

size_t Buffer::find(const std::string& str, size_t pos, size_t n)
{
    
    
    while (pos < this->_bufferUsed && pos < pos + n)
    {
        bool flag = true;

        for (int i = 0; 
                flag && i < str.size(); ++i)
        {
            if (pos + i < this->_bufferUsed || 
                pos + i >= pos + n ||
                this->_buffer.at(pos + i) != str.at(i))
                flag = false;
        }
        if (flag)
            return (pos);
        ++pos;
    }
    return (std::string::npos);
}

size_t Buffer::find(const char* str, size_t pos, size_t n)
{
    while (pos < this->_bufferUsed && pos < pos + n)
    {
        bool flag = true;

        for (int i = 0; 
                flag && str[i]; ++i)
        {
            if (pos + i < this->_bufferUsed ||
                pos + i >= pos + n ||
                this->_buffer.at(pos + i) != str[i])
                flag = false;
        }
        if (flag)
            return (pos);
        ++pos;
    }
    return (std::string::npos);
}

char& Buffer::at(size_t n)
{
    return (this->_buffer.at(n));
}

bool Buffer::startWith(const char& c, size_t pos, size_t n)
{
    return (!(n == 0 || this->_buffer.at(pos) != c ));
}

bool Buffer::startWith(const std::string& str, size_t pos, size_t n)
{
    return (find(str, pos , n < str.size() ? n : str.size()) != 
                std::string::npos);
}

bool Buffer::startWith(const char* str, size_t pos, size_t n)
{
    return (find(str, pos , n < std::strlen(str) ? n : std::strlen(str)) != 
                std::string::npos);
}

void Buffer::reset()
{
	this->_bufferUsed = 0;
	this->_bufferRead = 0;
}