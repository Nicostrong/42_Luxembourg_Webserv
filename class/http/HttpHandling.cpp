/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/30 15:54:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

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
    HttpResponse* resp = &sock->getResp();
    
    try
    {
		if (this->_parser.getState() == HttpParser::HTTP_HEADERS && 
			sock->getRxBuffer().getBufferUnread() > 0)
		{
			if (this->_state != CLIENT_RECEIVING_HEAD)
				setState(CLIENT_RECEIVING_HEAD);
		}

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
	this->_parser.setState(HttpParser::HTTP_BODY);
	setState(CLIENT_RECEIVING_BODY);
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
		time_t curr = time(NULL);

		switch (this->_state)
		{
			case IDLE:
				if (curr - this->_ts > IDLE_TIMEOUT)
					throw HttpSevereExceptions(HttpBase::REQUEST_TIMEOUT);
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
				//LOG_DEB("Checking sending");
				if (curr - this->_ts > CGI_SENDING_TIMEOUT)
					throw HttpExceptions(HttpBase::GATEWAY_TIMEOUT);
				break;
			case CGI_RECEIVING:
				//LOG_DEB("Checking receiving");
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
				if (this->_cgiResp.isError())
						throw HttpExceptions(this->_cgiResp.getErrorCode());
				switch (this->_cgiParser.getState())
				{
					case CgiParser::CGI_BODY_RECEIVED:
						this->_resHandling.init(*sock);
						em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLTICK | EPOLLHUP | EPOLLRDHUP);
						break;
					case CgiParser::CGI_HEAD:
					case CgiParser::CGI_BODY:
						if (this->_cgiResp.isEofReceived())
							throw HttpExceptions(HttpBase::BAD_GATEWAY);
						break;
					default:
						break;
				}
				// Handle Cgi Logic
			}
			else
			{
				this->_resHandling.init(*sock);
				em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLTICK | EPOLLHUP | EPOLLRDHUP);
			}
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
		em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLHUP | EPOLLRDHUP);
    }
	catch(const std::exception& e)
	{
		resp->setRespType(HttpResponse::ERROR);
		resp->setStatusCode(HttpBase::INTERNAL_SERVER_ERROR);
		this->_resHandling.init(*sock);
		em.monitorUpdate(sock->getSocket(), EPOLLOUT | EPOLLHUP | EPOLLRDHUP);
		LOG_ERROR(e.what());
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

void HttpHandling::reset()
{
	this->_parser.reset();
	this->_resHandling.reset();
	this->_cgiResp.reset();
	this->_cgiParser.setState(CgiParser::CGI_HEAD);
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
