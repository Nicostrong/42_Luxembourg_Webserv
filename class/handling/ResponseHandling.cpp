/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:11 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/03 09:14:19 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/handling/ResponseHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

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

ResponseHandling::State ResponseHandling::getState() const
{
	return (this->_state);
}

void ResponseHandling::init(Socket& sock)
{
	reset();
	
	if (sock.getDataSent())
	{
		this->_state = SENT;
		return ;
	}

    if (this->_state != NONE)
		return ;
	
	sock.getHandler().setState(HttpHandling::CLIENT_SENDING);
	
    switch (sock.getResp().getRespType())
    {
        case HttpResponse::REDIRECT:
			sock.getResp().sendHead(sock.getTxBuffer());
			sock.setReset();
			this->_state = SENT;
            break;
        case HttpResponse::CGI:
			CgiBody* body;

			body = sock.getHandler().getCgiResponse().getBody();
			if (body)
				sock.getResp().addHeader("Content-Length", body->getSize());
			else
				sock.getResp().addHeader("Content-Length", "0");
			sock.getResp().sendHead(sock.getTxBuffer());
            break;
        case HttpResponse::DIRECTORY_LISTING:
			sock.getResp().sendDirectoryListing(sock.getTxBuffer(), 
				sock.getReq());
			sock.setReset();
			this->_state = SENT;
            break;
        case HttpResponse::STATIC_FILE:
            try
            {
                this->_staticFile = new File(sock.getReq().getFilePath());
                sock.getResp().sendHead(sock.getTxBuffer());
            }
            catch(const std::exception& e)
            {
                throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
            }
            break;
        case HttpResponse::ERROR:
			if (sock.getReq().getCustomErrorPage())
			{
				try
            	{
					this->_staticFile = new File(sock.getReq().getCustomErrroPagePath());
					sock.getResp().sendHead(sock.getTxBuffer());
				}
				catch(const std::exception& e)
				{
					throw HttpExceptions(sock.getReq().getStatusCode());
				}
			}
			else
			{
				sock.getResp().sendDefaultErrorPage(sock.getTxBuffer());
				sock.setReset();
				this->_state = SENT;
			}
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
			sock.setReset();
        }
    }
	else if (sock.getResp().getRespType() == HttpResponse::CGI)
	{
		CgiBody* body = sock.getHandler().getCgiResponse().getBody();

		if (body)
		{
			if (body->read(sock.getTxBuffer()))
			{
				this->_state = SENT;
				sock.setReset();
			}
		}
		else
		{
			this->_state = SENT;
			sock.setReset();
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

       