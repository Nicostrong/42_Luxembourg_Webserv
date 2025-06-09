/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/09 23:38:15 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

HttpHandling::HttpHandling() {}

HttpHandling::~HttpHandling() {}

void HttpHandling::onRead(EventMonitoring& em, Socket* sock)
{
    HttpRequest* req = &sock->getReq();
    HttpResponse* resp = &sock->getResp();
    
    try
    {
        req->onRequest(sock->getRxBuffer(), *sock);
    
        if (req->getState() < HttpParser::HTTP_RECEIVED)
            return ;

        this->_resHandling.init(*sock);
        em.monitorUpdate(sock->getSocket(), POLLOUT | POLLHUP | POLLRDHUP);
    }
    catch(const HttpExceptions& e)
    {
        if (dynamic_cast<const HttpSevereExceptions*>(&e))
            setConnectionClose(*sock);
        if (e.getCode() > 399)
        {
		    LOG_ERROR("An error occured while parsing request (can be bad request as well)");
            LOG_ERROR(e.getCode());
        }
			
		resp->setRespType(HttpResponse::ERROR);
		resp->setStatusCode((HttpBase::HttpCode)e.getCode());
		this->_resHandling.init(*sock);
		em.monitorUpdate(sock->getSocket(), POLLOUT | POLLHUP | POLLRDHUP);
    }
}

void HttpHandling::onWrite(EventMonitoring& em, Socket* sock)
{
    (void)em;
    this->_resHandling.send(*sock);
}

void HttpHandling::setConnectionClose(Socket& sock)
{
    sock.setSocketClose();
	sock.getResp().addHeader("Connection", "close");
}

void HttpHandling::reset()
{
    this->_resHandling.reset();
}