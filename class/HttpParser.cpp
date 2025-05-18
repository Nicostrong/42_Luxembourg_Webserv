/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:36 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 11:12:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpParser.hpp"

HttpParser::HttpParser() : HttpBase(), _state(HTTP_STARTLINE) {}

HttpParser::HttpParser(const HttpParser& obj) : HttpBase(obj), 
	 _buffer(obj._buffer), _state(obj._state) {}

HttpParser::~HttpParser() {}

HttpParser& HttpParser::operator=(const HttpParser& obj)
{
	HttpBase::operator=(obj);
	this->_state = obj._state;
	this->_buffer = obj._buffer;
	return (*this);
}

void HttpParser::parse(std::vector<char>& buff, size_t n)
{
	size_t pos;

	this->_buffer.append(buff.data(), n);

	switch (this->_state)
	{
		// fallthrough
		case HttpParser::HTTP_STARTLINE:
			pos = this->_buffer.find(CRLF);
			if (pos == std::string::npos)
				return ;
			parseStartLine(this->_buffer.substr(0, pos));
			if (this->_state != HTTP_INVALID)
			{
				this->_state = HTTP_HEADERS;
				this->_buffer = this->_buffer.substr(pos + 2);
			}
		// fallthrough
		case HttpParser::HTTP_HEADERS:
			pos = this->_buffer.find(CRLF CRLF);
			if (pos == std::string::npos)
				return ;
			parseHeaders(this->_buffer.substr(0, pos));
			if (this->_state != HTTP_INVALID)
			{
				//if (this->_method)
				//this->_state = HTTP_BODY;
				this->_state = HTTP_RECEIVED;
				//this->_buffer = this->_buffer.substr(pos + 4);
			}
		case HttpParser::HTTP_BODY:
			// SHould check what to do depending
			break;
		default:
			break;
	}
}

void HttpParser::parseStartLine(const std::string& line)
{
	std::vector<std::string> tokens;
    std::istringstream iss(line);
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

void HttpParser::parseHeaders(const std::string& headers)
{
	size_t sPos = 0;
	size_t ePos = headers.find(CRLF);

	while (ePos != std::string::npos)
	{
		parseHeader(headers.substr(sPos, ePos));
		sPos = ePos + 2;
		ePos = headers.find(CRLF, sPos);
	}
	parseHeader(headers.substr(sPos));

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
