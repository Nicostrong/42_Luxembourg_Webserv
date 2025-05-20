/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:11 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/20 15:06:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseHandling.hpp"
#include "../includes/Socket.hpp"

ResponseHandling::ResponseHandling() : _staticFile(NULL), _state(NONE) {}

ResponseHandling::ResponseHandling(const ResponseHandling& obj) : 
    _staticFile(NULL), _state(obj._state) 
{
	if (obj._staticFile)
		this->_staticFile = new File(*obj._staticFile);
}

ResponseHandling::~ResponseHandling() 
{
    if (this->_staticFile)
        delete this->_staticFile;
}

ResponseHandling& ResponseHandling::operator=(const ResponseHandling& obj)
{
    (void)obj;
    return (*this);
}

void ResponseHandling::init(Socket& sock)
{
    if (this->_state != NONE)
		return ;
	
    switch (sock.getResp().getRespType())
    {
        case HttpResponse::REDIRECT:
			sock.getResp().sendHead(sock.getTxBuffer());
			sock.reset();
			this->_state = SENT;
            break;
        case HttpResponse::CGI:
            break;
        case HttpResponse::DIRECTORY_LISTING:
			sock.getResp().sendDirectoryListing(sock.getTxBuffer(), 
				sock.getReq());
			sock.reset();
			this->_state = SENT;
            break;
        case HttpResponse::STATIC_FILE:
            this->_staticFile = new File(sock.getReq().getFilePath());
			sock.getResp().sendHead(sock.getTxBuffer());
            break;
        case HttpResponse::ERROR:
			sock.getResp().sendDefaultErrorPage(sock.getTxBuffer());
			sock.reset();
			this->_state = SENT;
			break;
        default:
			break;
    }
    this->_state = INIT;
}

void ResponseHandling::send(Socket& sock)
{
	if (this->_state != INIT)
        return ;
    if (this->_staticFile)
    {
        this->_staticFile->read(sock.getTxBuffer(), MAX_READ_SIZE);
        if (this->_staticFile->getEof())
        {
			this->_state = SENT;
            delete this->_staticFile;
            this->_staticFile = NULL;
			sock.reset();
        }
    }
}

void ResponseHandling::reset()
{
	this->_state = NONE;
	if (this->_staticFile)
    	delete this->_staticFile;
    this->_staticFile = NULL;
}

       