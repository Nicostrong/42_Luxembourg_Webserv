/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 16:40:47 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() : HttpBase(), _charParsed(0), _isBadRequest(false), 
	_isReqReceived(false), _statusCode(OK) {}

HttpRequest::HttpRequest(const HttpRequest &obj) : HttpBase(obj)
{
	*this = obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		HttpBase::operator=(obj);
		this->_charParsed = obj._charParsed;
		this->_isBadRequest = obj._isBadRequest;
		this->_isReqReceived = obj._isReqReceived;
		this->_statusCode = obj._statusCode;
	}
	return (*this);
}

void HttpRequest::readReceived(int clientSocket, int serverSocket)
{
	(void)serverSocket;
	std::vector<char> buffer(BUFFER_SIZE);
	ssize_t bytes = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0);
	
	if (bytes == -1)
		throw SocketReadException();
	this->_raw.append(buffer.data(), bytes);
	parseRaw();
	if (this->_isReqReceived)
	{
		std::map<std::string, std::string>::const_iterator it;
		std::cout << "############ Headers ############" << std::endl;
		for (it = this->_headers.begin(); it != this->_headers.end(); it++)
		{
				std::cout << " " << it->first << " " << it->second << std::endl;
		}
		std::cout << "Request received completely!" << std::endl;
	}
}

bool HttpRequest::isBadRequest() const
{
	return (this->_statusCode == BAD_REQUEST);
}

HttpBase::HttpCode HttpRequest::getStatusCode() const
{
	return (this->_statusCode);
}

// Helpers

void HttpRequest::parseRaw()
{
	std::string line;
	size_t pos = this->_raw.find("\r\n");
	if (pos != std::string::npos && this->_charParsed == 0)
	{
		line = _raw.substr(0, pos);
		parseStartLine(line);
		this->_charParsed = pos + 2;
		if (this->_statusCode == BAD_REQUEST)
			return ;
	}
	while ((pos = this->_raw.find("\r\n", this->_charParsed)) != std::string::npos)
	{
		line = _raw.substr(this->_charParsed, pos - this->_charParsed);
		if (line.empty())
		{
			this->_body = _raw.substr(pos + 2);
			this->_isReqReceived = true;
			return ;
		}
		parseHeader(line);
		if (this->_statusCode == BAD_REQUEST)
			return ;
		this->_charParsed = pos + 2;
	}
}

void HttpRequest::parseStartLine(std::string &line)
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
		this->_statusCode = BAD_REQUEST;
		return ;
	}
	this->_method = tokens.at(0);
	this->_uri = tokens.at(1);
	this->_httpVersion = tokens.at(2);
	//std::cout << "Start line correct with METHOD = \"" << this->_method 
			  //<< "\" URI = \"" << this->_uri << "\" HTTP VERSION = \"" 
			  //<< this->_httpVersion << "\"" <<  std::endl;
}

void HttpRequest::parseHeader(std::string &line)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
	{
		this->_statusCode = BAD_REQUEST;
		return ;
	}

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
	{
		this->_statusCode = BAD_REQUEST;
		return ;
	}
	name = normalizeHeaderName(name);

	if (name == "host" && this->_headers.find(name) != this->_headers.end())
	{
		this->_statusCode = BAD_REQUEST;
		return;
	}

	this->_headers[name] = value;
}

// Exceptions
const char * HttpRequest::SocketReadException::what() const throw()
{
	return ("Read Exception");
}

const char * HttpRequest::RawUninitializedException::what() const throw()
{
	return ("Raw unitialized exception");
}