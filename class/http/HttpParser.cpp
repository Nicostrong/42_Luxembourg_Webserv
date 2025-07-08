/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:36 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/02 11:18:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpParser.hpp"
#include "./../../includes/networking/Socket.hpp"
#include "./../../includes/handling/RequestHandling.hpp"

HttpParser::HttpParser() : _state(HTTP_STARTLINE)
{
	this->_slBuffer.reserve(SL_BSIZE);
	this->_headBuffer.reserve(HEAD_BSIZE);
}

HttpParser::HttpParser(const HttpParser& obj) :_state(obj._state), 
	_slBuffer(obj._slBuffer), _headBuffer(obj._headBuffer)
{
	this->_slBuffer.reserve(SL_BSIZE);
	this->_headBuffer.reserve(HEAD_BSIZE);
}

HttpParser::~HttpParser() {}

HttpParser& HttpParser::operator=(const HttpParser& obj)
{
	if (this != &obj)
	{
		this->_state = obj._state;
		this->_slBuffer = obj._slBuffer;
		this->_headBuffer = obj._headBuffer;
	}
	return (*this);
}

HttpParser::State HttpParser::getState() const
{
	return (this->_state);
}

void HttpParser::setState(HttpParser::State state)
{
	this->_state = state;
}

void HttpParser::reset()
{
	this->_slBuffer.clear();
	this->_headBuffer.clear();
	this->_state = HTTP_STARTLINE;
}

void HttpParser::onRead(Buffer& buff, Socket& sock)
{
	switch (this->_state)
	{
		// fallthrough
		case HttpParser::HTTP_STARTLINE:
			if (!handleStartLine(buff, sock.getReq()))
				return ;
		// fallthrough
		case HttpParser::HTTP_HEADERS:
			handleHeaders(buff, sock.getReq());
			return ;
		case HttpParser::HTTP_BODY:
			if (!handleBody(buff, sock))
				return ;
		default:
			break;
	}
}

void HttpParser::parseStartLine(HttpRequest& req)
{
	std::vector<std::string> tokens;
    std::istringstream iss(this->_slBuffer);
    std::string token;

	while (iss >> token)
        tokens.push_back(token);
	
	if (tokens.size() != 3 || !HttpBase::canBeValidMethod(tokens.at(0)) || 
		!HttpBase::canBeValidPath(tokens.at(1)) ||
		!HttpBase::canBeValidHttpProtocol(tokens.at(2)))
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	size_t queryPos = tokens.at(1).find('?');
	
	req.setMethod(tokens.at(0));
	req.setUri(tokens.at(1).substr(0, queryPos));

	if (queryPos != std::string::npos)
		req.setQueryParams(tokens.at(1).substr(queryPos + 1));
	
	/* add extension attribute */
	size_t			dotPos = req.getUri().find('.');

	if (dotPos == req.getUri().npos)
		req.setExtension("");
	else
	{
		std::string		ext = req.getUri().substr(dotPos);
		size_t			slashPos = ext.find('/');

		if (slashPos == ext.npos)
			req.setExtension(ext);
		else
			req.setExtension(ext.substr(0, slashPos));
	}
	req.setHTTP(tokens.at(2));
}

void HttpParser::parseHeaders(HttpRequest& req)
{
	size_t sPos = 2;
	size_t ePos = this->_headBuffer.find(CRLF, sPos);

	while (ePos != std::string::npos)
	{
		parseHeader(this->_headBuffer.substr(sPos, ePos - sPos), req);
		sPos = ePos + 2;
		ePos = this->_headBuffer.find(CRLF, sPos);
	}
	
	if (this->_headBuffer.size())
		parseHeader(this->_headBuffer.substr(sPos), req);

	if (!req.findHeader("Host"))
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
}

void HttpParser::parseHeader(const std::string& line, HttpRequest& req)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!HttpBase::isHeaderNameValid(name))
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
	name = HttpBase::normalizeHeaderName(name);

	if (name == "Host" && req.findHeader("Host"))
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	req.addHeader(name, value);
}

// Helper

bool HttpParser::handleStartLine(Buffer& buff, HttpRequest& req)
{
	size_t len = std::min(buff.getBufferUnread(), 
		this->_slBuffer.capacity() - this->_slBuffer.size());
	
	this->_slBuffer.append(buff.getDataUnread(), len);
	
	size_t pos = this->_slBuffer.find(CRLF);
	
	if (pos == std::string::npos)
	{
		buff.setBufferRead(len);
		if (this->_slBuffer.size() >= this->_slBuffer.capacity())
			throw HttpSevereExceptions(HttpBase::URI_TOO_LONG);
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_slBuffer.size());
	this->_slBuffer.erase(pos);
	
	parseStartLine(req);
	if (this->_state == HTTP_STARTLINE)
		this->_state = HTTP_HEADERS;
	return (true);
}

bool HttpParser::handleHeaders(Buffer& buff, HttpRequest& req)
{
	size_t len = std::min(buff.getBufferUnread(), 
				this->_headBuffer.capacity() - this->_headBuffer.size());

	this->_headBuffer.append(buff.getDataUnread(), len);
	
	size_t pos = this->_headBuffer.find(CRLF CRLF);

	if (pos == std::string::npos)
	{
		buff.setBufferRead(len);

		if (this->_headBuffer.size() >= this->_headBuffer.capacity())
			throw HttpSevereExceptions(
				HttpBase::REQUEST_HEADER_FIELDS_TOO_LARGE);
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_headBuffer.size() + 4);
	this->_headBuffer.erase(pos);

	parseHeaders(req);
	if (this->_state == HTTP_HEADERS)
		this->_state = HTTP_HEAD_RECEIVED;
	return (true);
}

bool HttpParser::handleBody(Buffer& buff, Socket& sock)
{
	Body* body = sock.getReq().getBody();
	
	bool received = body->onRead(buff, sock);

	if (received)
		this->_state = HTTP_BODY_RECEIVED;
	return (received);
}
