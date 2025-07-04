/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiBody.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/04 14:18:54 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiBody.hpp"
#include "./../../includes/networking/Socket.hpp"

CgiBody::CgiBody( size_t bufferSize ) : Body(bufferSize) {}

CgiBody::~CgiBody() {}

bool CgiBody::onRead( Buffer& buff, Socket& sock )
{		
	if (sock.getHandler().getCgiResponse().isEof())
	{
		onBodyReceivedEof(buff);
		if (sock.getHandler().getCGI()->isOutputFinished())
		{
			this->_isReceived = true;
			return (true);
		}
	}
	else
		Body::onRead(buff, sock);
	
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
