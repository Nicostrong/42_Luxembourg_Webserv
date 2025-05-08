/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/08 16:10:57 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest(const std::string& remoteIp, 
	const std::string& remoteHost) : HttpBase(), _charParsed(0), 
	_isReceived(false), _remoteIp(remoteIp), _remoteHost(remoteHost) {}

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
		this->_isReceived = obj._isReceived;
		this->_pathTranslated = obj._pathTranslated;
		this->_remoteIp = obj._remoteIp;
		this->_remoteHost = obj._remoteHost;
	}
	return (*this);
}

void HttpRequest::readReceived(int clientSocket)
{
	std::vector<char> buffer(BUFFER_SIZE);
	if (this->_isReceived)
		return ;
	ssize_t bytes = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0);
	
	if (bytes == -1)
		throw SocketReadException();
	this->_raw.append(buffer.data(), bytes);
	parseRaw();
	if (this->_isReceived)
	{
		std::map<std::string, std::string>::const_iterator it;
		if (this->_statusCode != BAD_REQUEST)
			LOG_DEB(this->_method + " " + this->_uri + " " + this->_httpVersion);
	}
}

HttpBase::HttpCode HttpRequest::getStatusCode() const
{
	return (this->_statusCode);
}

bool HttpRequest::isReceived() const
{
	return (this->_isReceived);
}

// Helpers

void HttpRequest::parseRaw()
{
	std::string line;
	size_t pos;
	
	while ((pos = this->_raw.find("\r\n", this->_charParsed)) != std::string::npos)
	{
		line = _raw.substr(this->_charParsed, pos - this->_charParsed);
		if (this->_charParsed == 0)
			parseStartLine(line);
		else if (line.empty() && 
					this->_charParsed > 0 && 
					this->_headers.find("HOST") != this->_headers.end())
		{
			this->_body = _raw.substr(pos + 2);
			this->_statusCode = OK;
			this->_isReceived = true;
			return ;
		}
		else
			parseHeader(line);
		if (this->_isReceived)
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
		this->_isReceived = true;
		return ;
	}
	this->_method = tokens.at(0);
	this->_uri = tokens.at(1);
	this->_httpVersion = tokens.at(2);
}

void HttpRequest::parseHeader(std::string &line)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
	{
		this->_isReceived = true;
		return ;
	}

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
	{
		this->_isReceived = true;
		return ;
	}
	name = normalizeHeaderName(name);

	if (name == "HOST" && this->_headers.find(name) != this->_headers.end())
	{
		this->_isReceived = true;
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