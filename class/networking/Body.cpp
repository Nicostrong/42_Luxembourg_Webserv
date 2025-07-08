/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:20:30 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/06 15:29:52 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/networking/Body.hpp"
#include "../../includes/networking/Socket.hpp"

Body::Body(size_t bufferSize) : _buff(bufferSize), _size(0), _bytesRead(0), 
	_isReceived(false) {}

Body::~Body( void ) 
{
	if (!this->_fBuff.is_open())
		return ;
	
	this->_fBuff.flush();
	this->_fBuff.close();
	std::remove(this->_fName.c_str());
	
	return ;
}

const std::string&		Body::getTmpFileName( void ) const
{
	return (this->_fName);
}

void		Body::moveBodyFile( const std::string& name )
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
	return ;
}

bool		Body::onRead( Buffer& buff, Socket& sock )
{
	if (this->_isReceived)
		return (true);
		
	if (sock.getReq().isTE())
		onBodyReceivedTE(buff);
	else
		onBodyReceivedLength(buff, sock.getReq().getContentLength());
	return (this->_isReceived);
}

void		Body::onBodyReceivedLength( Buffer& buff, size_t bodyLen )
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
	{
		this->_fBuff.flush();
		this->_isReceived = true;
	}
	return ;
}

void		Body::onBodyReceivedTE( Buffer& buff )
{
	if (buff.getBufferUnread() < 1 || 
		this->_chunk.getState() == Chunk::CHUNK_END)
		return ;

	size_t		len = this->_chunk.handleChunk(buff);

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
	{
		this->_fBuff.flush();
		this->_isReceived = true;
	}
	return ;
}

size_t		Body::writeInMemory( Buffer& buff, size_t max )
{
	if (this->_size >= buff.getBufferSize())
		return (0);

	size_t		len = std::min(max, this->_buff.getBufferUnused());

	this->_buff.copyFrom(buff, buff.getBufferRead(), len);

	this->_size += len;
	buff.setBufferRead(len);

	return (len);
}

size_t		Body::writeInFile( Buffer& buff, size_t max )
{
	this->_fBuff.write(buff.getDataUnread(), max);
	if (this->_fBuff.fail()) 
		throw HttpSevereExceptions(HttpBase::INTERNAL_SERVER_ERROR);
	
	this->_size += max;
	buff.setBufferRead(max);
	
	return (max);
}

void		Body::openTmpFile( void )
{
	char*		tmpname;

	if (this->_fBuff.is_open())
		return ;
	
	for (int i = 0; !this->_fBuff.is_open() && i < MAX_RETRY; ++i)
	{
		tmpname = std::tmpnam(NULL);
		
		this->_fBuff.open(tmpname, 
			std::ios::in | std::ios::out | std::ios::trunc);
	}
	
	if (!this->_fBuff.is_open())
		throw HttpSevereExceptions(HttpBase::INTERNAL_SERVER_ERROR);
	
	this->_fName = tmpname;
	return ;
}

void		Body::readInFile( std::vector<char>& receivedTxtBuffer )
{
    std::string		filecontent;

    while(getline(_fBuff, filecontent))
    {
		std::string::iterator		it;

        for(it = filecontent.begin(); it != filecontent.end(); ++it)
            receivedTxtBuffer.push_back(*it);
        receivedTxtBuffer.push_back('\n');
    }
    _fBuff.close();
	return ;
}

bool		Body::read( Buffer& buff )
{
	if (!this->_fBuff.is_open() || this->_bytesRead >= this->_size)
		return (true);

	buff.resetIfRead();
	
	size_t freeSpace = buff.getBufferUnused();

	this->_fBuff.seekg(this->_bytesRead);
	this->_fBuff.read(buff.getDataUnused(), freeSpace);
	if (!this->_fBuff && !this->_fBuff.eof())
        throw std::runtime_error("Read failed");
	this->_bytesRead += this->_fBuff.gcount();
	buff.setBufferUsed(this->_fBuff.gcount());

	return (this->_fBuff.eof());
}

Buffer&		Body::getBuffer( void )
{
	return (this->_buff);
}

size_t Body::getSize()	const
{
	return (this->_size);
}

std::fstream& Body::getFstream()
{
	return (this->_fBuff);
}
