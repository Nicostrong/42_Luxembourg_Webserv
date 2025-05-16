/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 15:41:47 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core/chunking/Encoding.hpp"

Encoding::Encoding() 
{
    this->_receivedChunks.push(Chunk());
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
        this->_encodedChunk = obj._encodedChunk;
        this->_receivedChunks = obj._receivedChunks;
    }
    return (*this);    
}

std::string Encoding::decodeChunked(const std::vector<char>& buffer, size_t bytes)
{
    this->_encodedChunk.append(buffer.data(), bytes);

    this->_receivedChunks.back().decodeChunk(this->_encodedChunk);
    while (this->_encodedChunk.size() > 0 && 
        this->_receivedChunks.back().getState() == Chunk::CHUNK_REICEIVED)
    {
        this->_receivedChunks.push(Chunk());
        this->_receivedChunks.back().decodeChunk(this->_encodedChunk);
    }
}

const Chunk* Encoding::getFrontChunk() const
{
    return (&this->_receivedChunks.front());
}

void Encoding::popChunk()
{
    this->_receivedChunks.pop();
}
