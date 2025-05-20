/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 19:54:33 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/core/chunking/Encoding.hpp"

Encoding::Encoding() 
{
    this->_chunks.push(Chunk());
}

Encoding::Encoding(const Encoding& obj) 
{
    *this = obj;
}

Encoding::~Encoding() {}

Encoding& Encoding::operator=(const Encoding& obj)
{
    if (this != &obj)
    {
        this->_rawChunks = obj._rawChunks;
        this->_chunks = obj._chunks;
    }
    return (*this);    
}

void Encoding::decodeChunked(const std::vector<char>& buffer, size_t bytes)
{
    this->_rawChunks.append(buffer.data(), bytes);

    this->_chunks.back().decodeChunk(this->_rawChunks);
    while (this->_rawChunks.size() > 0 && 
        this->_chunks.back().getState() == Chunk::CHUNK_REICEIVED)
    {
        this->_chunks.push(Chunk());
        this->_chunks.back().decodeChunk(this->_rawChunks);
    }
}

void Encoding::encodeChunk(const std::vector<char>& buf, size_t n)
{
    this->_chunks.push(Chunk(buf, n));
}

const Chunk* Encoding::getFrontChunk() const
{
    return (&this->_chunks.front());
}

void Encoding::popChunk()
{
    this->_chunks.pop();
}
