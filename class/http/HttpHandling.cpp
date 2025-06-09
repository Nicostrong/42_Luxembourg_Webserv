/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/09 20:37:29 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpHandling.hpp"

HttpHandling::HttpHandling() {}

HttpHandling::~HttpHandling() {}

void HttpHandling::onRead(EventMonitoring& em, Socket& sock)
{
    HttpRequest* req = &sock.getReq();
    
    try
    {
        req->onRequest(sock.getRxBuffer(), sock);
    
        if (req->getState() < HttpParser::HTTP_RECEIVED)
            return ;

        this->_resHandling.init(sock);
        em.unmonitor(sock.getSocket());
        em.monitor(sock.getSocket(), POLLOUT | POLLHUP | POLLRDHUP,
            EventData::CLIENT, sock);
    }
    catch(const HttpExceptions& e)
    {
        if (dynamic_cast<const HttpSevereExceptions*>(&e))
		{
			this->_keepAlive = false;
			this->_resp.addHeader("Connection", "close");
		}
		LOG_ERROR("An error occured while parsing request (can be bad request as well)");
		LOG_ERROR(e.getCode());
			
		this->_resp.setRespType(HttpResponse::ERROR);
		this->_resp.setStatusCode((HttpBase::HttpCode)e.getCode());
		this->_rHandler.init(*this);
		em.unmonitor(sock.getSocket());
		em.monitor(sock.getSocket(), POLLOUT | POLLHUP | POLLRDHUP,
			EventData::CLIENT, *this);
    }
}

void HttpHandling::onWrite(EventMonitoring& em, Socket& sock)
{
    
}

void HttpHandling::setConnectionClose(Socket& sock)
{
    sock.setSocketClose();
	sock.getResp().addHeader("Connection", "close");
}