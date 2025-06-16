/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:04:52 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/16 18:29:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/Buffer.hpp"

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

const std::vector<char>&	Buffer::getVector() const
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

size_t Buffer::getBufferUsed() const
{
    return (this->_bufferUsed);
}

size_t Buffer::getBufferRead() const
{
    return (this->_bufferRead);
}

size_t Buffer::getBufferUnused() const
{
    return (this->_bufferSize - this->_bufferUsed);
}

size_t Buffer::getBufferUnread() const
{
    return (this->_bufferUsed - this->_bufferRead);
}

size_t Buffer::getBufferSize()	const
{
    return (this->_buffer.capacity());
}

void Buffer::setBufferRead(size_t n)
{
	size_t bRead = n + this->_bufferRead;
	
	if (bRead - n != this->_bufferRead || bRead >= this->_bufferUsed)
		this->_bufferRead = this->_bufferUsed;
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

bool Buffer::isBufferFull() const
{
	return (this->_bufferUsed == this->_bufferSize);
}

bool Buffer::isBufferRead() const
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
    size_t endPos = std::min(pos + n, buff._bufferUsed);

    if (pos >= endPos)
        return ;
    
    if (endPos - pos > getBufferUnused())
        throw NoSpaceAvailable();
    
    std::copy(buff.getVector().begin() + pos, 
                buff.getVector().begin() + endPos + 1, 
                    this->beginUnused());
    
    setBufferUsed(endPos - pos);
}

void Buffer::copyFrom(const std::string& buff, size_t pos, size_t n)
{
    size_t endPos = std::min(pos + n, buff.size());

    if (pos >= endPos)
        return ;
    
    if (endPos - pos > getBufferUnused())
        throw NoSpaceAvailable();
    
    std::copy(buff.begin() + pos, 
                buff.begin() + endPos + 1, 
                    this->beginUnused());
    
    setBufferUsed(endPos - pos);
}

size_t Buffer::find(const char& c, size_t pos, size_t n) const
{
    while (pos < this->_bufferUsed && pos < pos + n)
    {
        if (this->_buffer.at(pos) == c)
            return (pos);
        ++pos;
    }
    return (std::string::npos);
}

size_t Buffer::find(const std::string& str, size_t pos, size_t n) const
{
    
    
    while (pos < this->_bufferUsed && pos < pos + n)
    {
        bool flag = true;

        for (size_t i = 0; 
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

size_t Buffer::find(const char* str, size_t pos, size_t n) const
{
    size_t sLimit = std::min(pos + n, this->_bufferUsed);
    size_t strSize = std::strlen(str);
    
    if (strSize == 0 || pos + strSize > sLimit)
        return (std::string::npos);
        
    for (size_t j = pos; j <= sLimit - strSize; ++j)
    {
        bool match = true;

        for (size_t i = 0; match && i < strSize; ++i)
        {
            if (this->_buffer.at(j + i) != str[i])
                match = false;
        }
        if (match)
            return (j);
    }
    return (std::string::npos);
}

char& Buffer::at(size_t n)
{
    return (this->_buffer.at(n));
}

const char& Buffer::at(size_t n) const
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

void Buffer::alignData()
{
    if (!this->_bufferRead)
        return ;
    
    std::memmove(this->_buffer.data(), getDataUnread(), getBufferUnread());
    
    this->_bufferUsed -= this->_bufferRead;
    this->_bufferRead = 0;
}

void Buffer::reset()
{
	this->_bufferUsed = 0;
	this->_bufferRead = 0;
}

void Buffer::resetIfRead()
{
    if (isBufferRead())
        reset();
}

// Exceptions

const char *Buffer::NoSpaceAvailable::what() const throw()
{
	return ("No space available in buffer");
}

std::ostream& operator<<(std::ostream& os, const Buffer& obj)
{
    os << "Buffer Max Size: " << obj.getVector().capacity() << " Curr Size: " 
       << obj.getBufferUnread() << std::endl;
    
    os << "\"";
    
    for (size_t i = obj.getBufferRead(); i < obj.getBufferUsed(); ++i)
    {
        const char c = obj.at(i);
        os << (std::isprint(c) ? c : (int)c) << " ";
    }
    os << "\"" << std::endl;
    return (os);
}