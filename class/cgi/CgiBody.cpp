/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiBody.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/04 16:19:13 by fdehan           ###   ########.fr       */
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
