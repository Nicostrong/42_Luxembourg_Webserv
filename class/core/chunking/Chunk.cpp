/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:55:18 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 10:40:29 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/core/chunking/Chunk.hpp"

Chunk::Chunk() : _state(CHUNK_LEN), _len(0), _dataSent(0) {}

Chunk::Chunk(const std::vector<char>& buffer, size_t bytes) : 
    _state(CHUNK_REICEIVED), _dataSent(0)
{
    this->_len = bytes;
    this->_data.append(buffer.data(), bytes);
    encodeChunk();
}

Chunk::Chunk(const Chunk& obj) 
{
    *this = obj;
}

Chunk::~Chunk() {}

Chunk &Chunk::operator=(const Chunk& obj)
{
    if (this != &obj)
    {
        this->_state = obj._state;
        this->_len = obj._len;
        this->_data = obj._data;
        this->_dataSent = obj._dataSent;
        this->_encoded = obj._encoded;
    }
    return (*this);
}

void Chunk::decodeChunk(std::string& data)
{
    size_t pos;
    
    switch (this->_state)
    {
        // fallthrough
        case CHUNK_LEN:
            pos = data.find(CRLF);
            pos = std::min(data.find(";"), pos);
            if (!pos)
                throw std::runtime_error("Bad Request");
            if (pos == std::string::npos)
                return ; 
            this->_len = convertHexa(
                data.substr(0, pos - 1));
            if (data.at(pos) == ';')
            {
                this->_state = CHUNK_EXT;
                data = data.substr(pos + 1);
            }
            else
            {
                this->_state = CHUNK_DATA;
                data = data.substr(pos + 2);
            }
        // fallthrough
        case CHUNK_EXT:
            pos = data.find(CRLF);
            if (pos == std::string::npos)
                return ;
            this->_state = CHUNK_DATA;
            data= data.substr(pos + 2);
        // fallthrough
        case CHUNK_DATA:
            if (data.size() >= this->_len + 2)
            {
                if (data.find(CRLF, this->_len) != this->_len)
                    throw std::runtime_error("Bad Request");
                this->_state = CHUNK_REICEIVED;
                this->_data = data.substr(0, this->_len);
                data = data.substr(this->_len + 2);
            }
            break;
        default:
            break;
    }
}

Chunk::State   Chunk::getState() const
{
    return (this->_state);
}

void Chunk::encodeChunk()
{
    std::ostringstream oss;

    oss << std::hex << this->_len << CRLF
        << this->_data << CRLF;

    this->_encoded = oss.str();
}

//Helpers

size_t Chunk::convertHexa(const std::string& str)
{
    std::istringstream iss(str);
    size_t res;

    iss >> std::hex >> res;
    if (iss.fail()) 
        throw std::runtime_error("Bad Request");
    return (res);
}