/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 10:02:09 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Encoding.hpp"

Encoding::Encoding() : _state(CHUNK_LEN), _chunkLen(0) {}

Encoding::Encoding(const Encoding& obj) 
{
    *this = obj;
}

Encoding::~Encoding() {}

Encoding& Encoding::operator=(const Encoding& obj)
{
    if (this != &obj)
    {
        this->_encodedChunk = obj._encodedChunk;
        this->_state = obj._state;
        this->_chunkLen = obj._chunkLen;
    }
    return (*this);    
}

std::string Encoding::encodeChunk(const std::vector<char>& buffer, size_t bytes)
{
    std::ostringstream oss;

    oss << std::hex << bytes << CRLF;
    oss.write(buffer.data(), bytes);
    oss << CRLF;

    return (oss.str());
}

std::string Encoding::decodeChunk(const std::vector<char>& buffer, size_t bytes)
{
    size_t pos = 1;
    
    this->_encodedChunk.append(buffer.data(), bytes);
    while (this->_encodedChunk.size() > 0 && pos != std::string::npos)
    {
        switch (this->_state)
        {
            case CHUNK_LEN:
                pos = this->_encodedChunk.find(CRLF);
                pos = std::min(this->_encodedChunk.find(";"), pos);
                if (!pos)
                    throw std::runtime_error("Bad Request");
                if (pos != std::string::npos)
                {
                    this->_chunkLen = convertHexa(
                        this->_encodedChunk.substr(0, pos - 1));
                    if (this->_encodedChunk.at(pos) == ';')
                    {
                        this->_state = CHUNK_EXT;
                        this->_encodedChunk = 
                            this->_encodedChunk.substr(pos + 1);
                    }
                    else
                    {
                        this->_state = CHUNK_DATA;
                        this->_encodedChunk = 
                            this->_encodedChunk.substr(pos + 2);
                    } 
                }
                break;
            case CHUNK_EXT:
                pos = this->_encodedChunk.find(CRLF);
                if (pos != std::string::npos)
                {
                    this->_state = CHUNK_DATA;
                    this->_encodedChunk= this->_encodedChunk.substr(pos + 2);
                }
                break;
            case CHUNK_DATA:
                break;
            case CHUNK_END:
                break;

        }
    }
}

//Helpers

size_t Encoding::convertHexa(const std::string& str)
{
    std::istringstream iss(str);
    size_t res;

    iss >> std::hex >> res;
    if (iss.fail()) 
        throw std::runtime_error("Bad Request");
    return (res);
}

