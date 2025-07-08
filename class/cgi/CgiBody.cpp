/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiBody.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:06:49 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiBody.hpp"
#include "./../../includes/networking/Socket.hpp"

CgiBody::CgiBody( size_t bufferSize ) : Body(bufferSize) {}

CgiBody::~CgiBody() {}

bool CgiBody::onRead( Buffer& buff, Socket& sock )
{
	if (this->_isReceived)
		return (true);

	CgiResponse* cgiResp = &sock.getHandler().getCgiResponse();
	
	if (sock.getHandler().getCgiResponse().isEof())
	{
		onBodyReceivedEof(buff);
		if (sock.getHandler().getCGI()->isOutputFinished())
			this->_isReceived = true;
	}
	else if (cgiResp->isTE())
		onBodyReceivedTE(buff);
	else
		onBodyReceivedLength(buff, cgiResp->getContentLength());
	
	return (this->_isReceived);
}

void CgiBody::onBodyReceivedEof( Buffer& buff )
{
	if (buff.getBufferUnread() < 1)
		return ;
	writeInMemory(buff, buff.getBufferUnread());
	
	if (buff.getBufferUnread() < 1)
		return ;

	openTmpFile();
	writeInFile(buff, buff.getBufferUnread());
	
	this->_fBuff.flush();
}

void CgiBody::onBodyReceivedTE( Buffer& buff )
{
	if (buff.getBufferUnread() < 1 || 
		this->_cgiChunk.getState() == CgiChunk::CHUNK_END)
		return ;

	size_t		len = this->_cgiChunk.handleChunk(buff);

	while (len > 0 || this->_cgiChunk.getState() == CgiChunk::CHUNK_START)
	{
		len -= writeInMemory(buff, len);

		if (len > 0)
		{
			openTmpFile();
			writeInFile(buff, len);
		}

		len = this->_cgiChunk.handleChunk(buff);
	}

	if (this->_cgiChunk.getState() == CgiChunk::CHUNK_END)
	{
		this->_fBuff.flush();
		this->_isReceived = true;
	}
	return ;
}
