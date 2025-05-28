/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:36 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 21:36:23 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpParser.hpp"

HttpParser::HttpParser() : HttpBase(), _state(HTTP_STARTLINE), 
	_bodyBuffer(BODY_BUFFER_SIZE) 
	{
		this->_slBuffer.reserve(SL_BSIZE);
		this->_headBuffer.reserve(HEAD_BSIZE);
	}

HttpParser::HttpParser(const HttpParser& obj) : HttpBase(obj), 
	_state(obj._state), _slBuffer(obj._slBuffer), _headBuffer(obj._headBuffer), 
	_bodyBuffer(obj._bodyBuffer) 
{
	this->_slBuffer.reserve(SL_BSIZE);
	this->_headBuffer.reserve(HEAD_BSIZE);
}

HttpParser::~HttpParser() {}

HttpParser& HttpParser::operator=(const HttpParser& obj)
{
	HttpBase::operator=(obj);
	this->_state = obj._state;
	this->_slBuffer = obj._slBuffer;
	this->_headBuffer = obj._headBuffer;
	this->_bodyBuffer = obj._bodyBuffer;
	return (*this);
}

void HttpParser::parse(Buffer& buff)
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
			break;
		case HttpParser::HTTP_BODY:
			// SHould check what to do depending
			break;
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
	{
		this->_state = HTTP_INVALID;
		return ;
	}

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
		parseHeader(this->_headBuffer.substr(sPos, ePos));
		sPos = ePos + 2;
		ePos = this->_headBuffer.find(CRLF, sPos);
	}
	parseHeader(this->_headBuffer.substr(sPos));

	if (this->_headers.find("HOST") == this->_headers.end())
	{
		this->_state = HTTP_INVALID;
		return ;
	}
}

void HttpParser::parseHeader(const std::string& line)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
	{
		this->_state = HTTP_INVALID;
		return ;
	}

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
	{
		this->_state = HTTP_INVALID;
		return ;
	}
	name = normalizeHeaderName(name);

	if (name == "HOST" && this->_headers.find(name) != this->_headers.end())
	{
		this->_state = HTTP_INVALID;
		return;
	}

	this->_headers[name] = value;
}

HttpParser::State HttpParser::getState() const
{
	return (this->_state);
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
			this->_state = HTTP_SL_TOOBIG;
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
			this->_state = HTTP_HEAD_TOOBIG;
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_headBuffer.size() + 4);
	this->_headBuffer.erase(pos);

	parseHeaders();
	if (this->_state == HTTP_HEADERS)
		this->_state = HTTP_RECEIVED;
	return (true);
}
