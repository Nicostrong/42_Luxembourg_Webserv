/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:20:30 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/30 11:19:33 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/RequestBody.hpp"
#include "./../includes/Socket.hpp"

RequestBody::RequestBody(size_t bufferSize) : _buff(bufferSize), _size(0) {}

RequestBody::~RequestBody() 
{
	if (!this->_fBuff.is_open())
		return ;
	
    this->_fBuff.flush();
    this->_fBuff.close();
	std::remove(this->_fName.c_str());
}

const std::string& RequestBody::getTmpFileName() const
{
	return (this->_fName);
}

void RequestBody::moveBodyFile(const std::string& name)
{
	if (!this->_fBuff.is_open() || this->_fName.empty())
	{
		std::ofstream dst(name.c_str(), std::ios::binary);

		if (!dst)
			throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
		
		dst.close();
		return ;
	}
	
	this->_fBuff.flush();
    this->_fBuff.close();
	
	if(std::rename(this->_fName.c_str(), name.c_str()) < 0) 
	{
		std::ifstream src(this->_fName.c_str(), std::ios::binary);
        std::ofstream dst(name.c_str(), std::ios::binary);

		if (!src || !dst) {
            throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
        }
        
        dst << src.rdbuf();
        
        if (dst.fail()) {
            throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
        }
        
        src.close();
        dst.close();
        std::remove(this->_fName.c_str());
	}
}

bool RequestBody::onBodyReceived(Buffer& buff, Socket& sock)
{
	if (sock.getReq().isTE())
	{
		onBodyReceivedTE(buff);
		return (this->_chunk.getState() == Chunk::CHUNK_END);
	}
	else
	{
		onBodyReceivedLength(buff, sock.getReq().getContentLength());
		return (this->_size >= sock.getReq().getContentLength());
	}
}

void RequestBody::onBodyReceivedLength(Buffer& buff, size_t bodyLen)
{
	if (buff.getBufferUnread() < 1)
		return ;
	writeInMemory(buff, 
		std::min(bodyLen - this->_size, buff.getBufferUnread()));
	
	if (buff.getBufferUnread() < 1)
		return ;

	openTmpFile();
	writeInFile(buff, 
		std::min(bodyLen - this->_size, buff.getBufferUnread()));
	
	if (this->_size >= bodyLen)
		this->_fBuff.flush();
}

void RequestBody::onBodyReceivedTE(Buffer& buff)
{
	if (buff.getBufferUnread() < 1 || 
		this->_chunk.getState() == Chunk::CHUNK_END)
		return ;
	size_t len = this->_chunk.handleChunk(buff);

	while (len > 0 || this->_chunk.getState() == Chunk::CHUNK_START)
	{
		len -= writeInMemory(buff, len);

		if (len > 0)
		{
			openTmpFile();
			writeInFile(buff, len);
		}

		len = this->_chunk.handleChunk(buff);
	}

	if (this->_chunk.getState() == Chunk::CHUNK_END)
		this->_fBuff.flush();
}

size_t RequestBody::writeInMemory(Buffer& buff, size_t max)
{
	if (this->_size >= buff.getBufferSize())
		return (0);

	size_t len = std::min(max, this->_buff.getBufferUnused());
	this->_buff.copyFrom(buff, buff.getBufferRead(), len);

	this->_size += len;
	buff.setBufferRead(len);

	return (len);
}

size_t RequestBody::writeInFile(Buffer& buff, size_t max)
{
	this->_fBuff.write(buff.getDataUnread(), max);
	if (this->_fBuff.fail()) 
		throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
	
	this->_size += max;
	buff.setBufferRead(max);
	
	return (max);
}

void RequestBody::openTmpFile()
{
	char* tmpname;

	if (this->_fBuff.is_open())
		return ;
	
	for (int i = 0; !this->_fBuff.is_open() && i < MAX_RETRY; ++i)
	{
		tmpname = std::tmpnam(NULL);
		
		this->_fBuff.open(tmpname, 
			std::ios::in | std::ios::out | std::ios::trunc);
	}
	
	if (!this->_fBuff.is_open())
		throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
	
	this->_fName = tmpname;
}
