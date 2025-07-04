/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/04 11:05:52 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpHandling.hpp"
#include "./../../includes/networking/Socket.hpp"
#include "./../../includes/networking/SocketManager.hpp"

HttpHandling::HttpHandling() : _cgi(NULL), _ts(time(NULL)), _state(CLIENT_RECEIVING_HEAD) {}

HttpHandling::~HttpHandling()
{
	if (this->_cgi)
		delete this->_cgi;
	this->_cgi = NULL;
	return ;
}

void HttpHandling::onRead(EventMonitoring& em, Socket* sock)
{
    (void)em;

	if (this->_parser.getState() == HttpParser::HTTP_HEADERS && 
		sock->getRxBuffer().getBufferUnread() > 0)
	{
		if (this->_state != CLIENT_RECEIVING_HEAD)
			setState(CLIENT_RECEIVING_HEAD);
	}

	this->_parser.onRead(sock->getRxBuffer(), *sock);
}

void HttpHandling::setBodyRequired(Socket& sock)
{
	HttpRequest* req = &sock.getReq();
	Body* body = req->getBody();
	
	this->_parser.setState(HttpParser::HTTP_BODY);
	
	if (!body)
	{
		body = new Body(0);

		if (!body)
			throw HttpSevereExceptions(HttpBase::INTERNAL_SERVER_ERROR);

		req->setBody(body);
	}
	
	setState(CLIENT_RECEIVING_BODY);
}

void HttpHandling::onWrite(EventMonitoring& em, Socket* sock)
{
	(void)em;
	this->_resHandling.send(*sock);
}

void HttpHandling::onTick(EventMonitoring& em, Socket* sock)
{
	time_t curr = time(NULL);

	switch (this->_state)
	{
		case IDLE:
			if (curr - this->_ts > IDLE_TIMEOUT)
			{
				LOG_DEB("IDLE limit reached");
				sock->getSockM().remove(*sock, em);
				return ;
			}
			break;
		case CLIENT_RECEIVING_HEAD:
			if (curr - this->_ts > CLIENT_RECEIVING_HEAD_TIMEOUT)
				throw HttpSevereExceptions(HttpBase::REQUEST_TIMEOUT);
			break;
		case CLIENT_RECEIVING_BODY:
			if (curr - this->_ts > CLIENT_RECEIVING_BODY_TIMEOUT)
				throw HttpSevereExceptions(HttpBase::REQUEST_TIMEOUT);
			break;
		case CLIENT_SENDING:
			if (curr - this->_ts > CLIENT_SENDING_TIMEOUT)
				throw HttpSevereExceptions(HttpBase::SERVICE_UNAVAILABLE);
			break;
		case CGI_SENDING:
			if (curr - this->_ts > CGI_SENDING_TIMEOUT)
				throw HttpExceptions(HttpBase::GATEWAY_TIMEOUT);
			break;
		case CGI_RECEIVING:
			if (curr - this->_ts > CGI_RECEIVING_TIMEOUT)
				throw HttpExceptions(HttpBase::GATEWAY_TIMEOUT);
			break;
		default:
			break;
	}

	if (this->_resHandling.getState() != ResponseHandling::NONE)
		return ;

	switch (this->_parser.getState())
	{
		case HttpParser::HTTP_HEAD_RECEIVED:
			RequestHandling::handleHeaders(*sock);
			if (this->_parser.getState() == HttpParser::HTTP_BODY)
				onRead(em, sock);
			break;
		case HttpParser::HTTP_BODY_RECEIVED:
			RequestHandling::handleBody(*sock);
			break;
		default:
			break;
	}

	if (this->_parser.getState() == HttpParser::HTTP_HANDLED)
	{
		HttpResponse* resp = &sock->getResp();

		if (resp->getRespType() == HttpResponse::CGI)
		{
			em.monitorUpdate(sock->getSocket(), EPOLLTICK | EPOLLHUP | EPOLLRDHUP);
			this->_cgi->onTickEvent(0, em);

			if (this->_cgiResp.isError())
					throw HttpExceptions(this->_cgiResp.getErrorCode());
			
			if (!this->_cgi->isCgiFinished())
				return ;
			
			if (this->_cgiParser.getState() == CgiParser::CGI_BODY_RECEIVED)
			{
				this->_resHandling.init(*sock);
				em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLTICK | EPOLLHUP | EPOLLRDHUP);
			}
		}
		else
		{
			this->_resHandling.init(*sock);
			em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLTICK | EPOLLHUP | EPOLLRDHUP);
		}
	}
}

void HttpHandling::setConnectionClose(Socket& sock)
{
	sock.setSocketClose();
	sock.getResp().addHeader("Connection", "close");
}

void HttpHandling::setState(State state)
{
	this->_ts = time(NULL);
	this->_state = state;
}

void HttpHandling::onCgiComplete()
{
	
}

void HttpHandling::reset()
{
	this->_parser.reset();
	this->_resHandling.reset();
	this->_cgiResp.reset();
	this->_cgiParser.reset();
	if (this->_cgi)
		delete this->_cgi;
	this->_cgi = NULL;
	setState(IDLE);
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

CgiResponse& HttpHandling::getCgiResponse()
{
	return (this->_cgiResp);
}

ResponseHandling& HttpHandling::getResponseHandling()
{
	return (this->_resHandling);
}

HttpParser& HttpHandling::getHttpParser()
{
	return (this->_parser);
}
