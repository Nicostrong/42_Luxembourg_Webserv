/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:36 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/30 13:18:39 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpParser.hpp"
#include "../includes/Socket.hpp"
#include "../includes/RequestHandling.hpp"

HttpParser::HttpParser() : HttpBase(), _state(HTTP_STARTLINE), _reqBody(NULL)
	{
		this->_slBuffer.reserve(SL_BSIZE);
		this->_headBuffer.reserve(HEAD_BSIZE);
	}

HttpParser::HttpParser(const HttpParser& obj) : HttpBase(obj), 
	_state(obj._state), _slBuffer(obj._slBuffer), _headBuffer(obj._headBuffer), 
	_reqBody(NULL)
{
	this->_slBuffer.reserve(SL_BSIZE);
	this->_headBuffer.reserve(HEAD_BSIZE);
}

HttpParser::~HttpParser() {}

HttpParser& HttpParser::operator=(const HttpParser& obj)
{
	if (this != &obj)
	{
		HttpBase::operator=(obj);
		this->_state = obj._state;
		this->_slBuffer = obj._slBuffer;
		this->_headBuffer = obj._headBuffer;
		if (this->_reqBody)
			delete this->_reqBody;
		LOG_DEB("Request reseted");
		this->_reqBody = obj._reqBody;
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

RequestBody* HttpParser::getBody() const
{
	return (this->_reqBody);
}

void HttpParser::onRequest(Buffer& buff, Socket& sock)
{
	switch (this->_state)
	{
		// fallthrough
		case HttpParser::HTTP_STARTLINE:
			if (!handleStartLine(buff))
				return ;
		// fallthrough
		case HttpParser::HTTP_HEADERS:
			if (!handleHeaders(buff))
				return ;
		// fallthrough
		case HttpParser::HTTP_HEAD_HANDLING:
			this->_state = HTTP_RECEIVED;
			RequestHandling::handleHeaders(sock);
			if (this->_state == HTTP_RECEIVED)
				return ;
		// fallthrough
		case HttpParser::HTTP_BODY:
			if (!handleBody(buff, sock))
				return ;
		// fallthrough
		case HttpParser::HTTP_BODY_HANDLING:
			this->_state = HTTP_RECEIVED;
			RequestHandling::handleBody(sock);
		default:
			break;
	}
}

void HttpParser::parseStartLine()
{
	std::vector<std::string> tokens;
    std::istringstream iss(this->_slBuffer);
    std::string token;

	while (iss >> token) {
        tokens.push_back(token);
    }
	
	if (tokens.size() != 3 || !canBeValidMethod(tokens.at(0)) || 
		!canBeValidPath(tokens.at(1)) || !canBeValidHttpProtocol(tokens.at(2)))
		throw HttpExceptions(BAD_REQUEST);

	//size_t queryPos = tokens.at(1).find('?');
	this->_method = tokens.at(0);
	this->_uri = tokens.at(1);//.substr(0, queryPos);
	//if (queryPos != std::string::npos)
	//	this->_queryParams = tokens.at(1).substr(queryPos + 1);
	this->_httpVersion = tokens.at(2);
}

void HttpParser::parseHeaders()
{
	size_t sPos = 0;
	size_t ePos = this->_headBuffer.find(CRLF);

	while (ePos != std::string::npos)
	{
		parseHeader(this->_headBuffer.substr(sPos, ePos - sPos));
		sPos = ePos + 2;
		ePos = this->_headBuffer.find(CRLF, sPos);
	}
	parseHeader(this->_headBuffer.substr(sPos));

	if (this->_headers.find("HOST") == this->_headers.end())
		throw HttpExceptions(BAD_REQUEST);
}

void HttpParser::parseHeader(const std::string& line)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
		throw HttpExceptions(BAD_REQUEST);

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
		throw HttpExceptions(BAD_REQUEST);
	name = normalizeHeaderName(name);

	if (name == "HOST" && this->_headers.find(name) != this->_headers.end())
		throw HttpExceptions(BAD_REQUEST);

	this->_headers[name] = value;
}

// Helper

bool HttpParser::handleStartLine(Buffer& buff)
{
	size_t len = std::min(buff.getBufferUnread(), 
		this->_slBuffer.capacity() - this->_slBuffer.size());
	
	this->_slBuffer.append(buff.getDataUnread(), len);
	
	size_t pos = this->_slBuffer.find(CRLF);
	
	if (pos == std::string::npos)
	{
		buff.setBufferRead(len);
		if (this->_slBuffer.size() >= this->_slBuffer.capacity())
			throw HttpExceptions(URI_TOO_LONG);
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_slBuffer.size() + 2);
	this->_slBuffer.erase(pos);
	
	parseStartLine();
	if (this->_state == HTTP_STARTLINE)
		this->_state = HTTP_HEADERS;
	return (true);
}

bool HttpParser::handleHeaders(Buffer& buff)
{
	size_t len = std::min(buff.getBufferUnread(), 
				this->_headBuffer.capacity() - this->_headBuffer.size());

	this->_headBuffer.append(buff.getDataUnread(), len);
	
	size_t pos = this->_headBuffer.find(CRLF CRLF);

	if (pos == std::string::npos)
	{
		buff.setBufferRead(len);

		if (this->_headBuffer.size() >= this->_headBuffer.capacity())
			throw HttpExceptions(REQUEST_HEADER_FIELDS_TOO_LARGE);
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_headBuffer.size() + 4);
	this->_headBuffer.erase(pos);

	parseHeaders();
	if (this->_state == HTTP_HEADERS)
		this->_state = HTTP_HEAD_HANDLING;
	return (true);
}

bool HttpParser::handleBody(Buffer& buff, Socket& sock)
{
	if (!this->_reqBody)
		this->_reqBody = new RequestBody(0);
	return (this->_reqBody->onBodyReceived(buff, sock));
}
