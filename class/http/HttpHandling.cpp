/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 17:41:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

HttpHandling::HttpHandling() : _cgi(NULL) {}

HttpHandling::~HttpHandling()
{
	if (this->_cgi)
		delete this->_cgi;
	this->_cgi = NULL;
	return ;
}

void HttpHandling::onRead(EventMonitoring& em, Socket* sock)
{
    HttpResponse* resp = &sock->getResp();
    
    try
    {
        this->_parser.onRead(sock->getRxBuffer(), *sock);
    }
    catch(const HttpExceptions& e)
    {
        if (dynamic_cast<const HttpSevereExceptions*>(&e))
            setConnectionClose(*sock);
        if (e.getCode() > 399)
        {
            LOG_DEB(this->_parser.getState());
		    LOG_ERROR("An error occured while parsing request (can be bad request as well)");
            LOG_ERROR(e.getCode());
        }
			
		resp->setRespType(HttpResponse::ERROR);
		resp->setStatusCode((HttpBase::HttpCode)e.getCode());
		this->_resHandling.init(*sock);
		em.monitorUpdate(sock->getSocket(), POLLOUT | EPOLLTICK | POLLHUP | POLLRDHUP);
    }
}

void HttpHandling::setBodyRequired()
{
	if (this->_parser.getState() == HttpParser::HTTP_HEAD_RECEIVED)
		this->_parser.setState(HttpParser::HTTP_BODY);
}

void HttpHandling::onWrite(EventMonitoring& em, Socket* sock)
{
	(void)em;
	this->_resHandling.send(*sock);
}

void HttpHandling::onTick(EventMonitoring& em, Socket* sock)
{
	HttpResponse* resp = &sock->getResp();
	
	try
    {
		switch (this->_parser.getState())
			{
				case HttpParser::HTTP_HEAD_RECEIVED:
					RequestHandling::handleHeaders(*sock);
					break;
				case HttpParser::HTTP_BODY_RECEIVED:
					RequestHandling::handleBody(*sock);
					break;
				default:
					return ;
			}

		switch (this->_parser.getState())
		{
			case HttpParser::HTTP_HEAD_RECEIVED:
			// fallthrough
			case HttpParser::HTTP_BODY_RECEIVED:
				if (sock->getResp().getRespType() == HttpResponse::CGI)
				{
					em.monitorUpdate(sock->getSocket(), EPOLLHUP | EPOLLRDHUP);
					sock->getResp().setRespType(HttpResponse::ERROR);
				}
				this->_resHandling.init(*sock);
				
				break;
			default:
				return ;
		}
	}
	catch(const HttpExceptions& e)
    {
        if (dynamic_cast<const HttpSevereExceptions*>(&e))
            setConnectionClose(*sock);
        if (e.getCode() > 399)
        {
            LOG_DEB(this->_parser.getState());
		    LOG_ERROR("An error occured while parsing request (can be bad request as well)");
            LOG_ERROR(e.getCode());
        }
			
		resp->setRespType(HttpResponse::ERROR);
		resp->setStatusCode((HttpBase::HttpCode)e.getCode());
		this->_resHandling.init(*sock);
		em.monitorUpdate(sock->getSocket(), POLLOUT | EPOLLTICK | POLLHUP | POLLRDHUP);
    }
}

void HttpHandling::setConnectionClose(Socket& sock)
{
	sock.setSocketClose();
	sock.getResp().addHeader("Connection", "close");
}

void HttpHandling::reset()
{
	this->_parser.reset();
	this->_resHandling.reset();
	this->_cgiResp.reset();
	if (this->_cgi)
		delete this->_cgi;
	this->_cgi = NULL;
	return ;
}

void		HttpHandling::setCGI( Socket& socket )
{
	this->_cgi = new MyCGI(socket);
	return ;
}

MyCGI*		HttpHandling::getCGI( void )
{
	return (this->_cgi);
}

CgiParser& HttpHandling::getCgiParser()
{
	return (this->_cgiParser);
}