/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 11:11:52 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core/chunking/Encoding.hpp"

Encoding::Encoding() {}

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
                if (this->_encodedChunk.size() >= this->_chunkLen + 2)
                {
                    if (this->_encodedChunk.find(CRLF, this->_chunkLen) != 
                        this->_chunkLen)
                        throw std::runtime_error("Bad Request");
                    //Should put the data somewhere
                }
                break;
            case CHUNK_END:
                break;
        }
    }
}

