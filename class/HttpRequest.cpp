/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/23 17:10:42 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() :  _raw(""), _charParsed(0),_isBadRequest(false), 
	_method(""), _uri(""), _httpVersion(""), _body(""), _isReqReceived(false) {}

HttpRequest::HttpRequest(const HttpRequest &obj) : _raw(""),  _charParsed(0), 
	_isBadRequest(false), _method(""), _uri(""), _httpVersion(""), _body(""), 
	_isReqReceived(false)
{
	*this = obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		this->_raw = obj._raw;
		this->_isBadRequest = obj._isBadRequest;
		this->_headers = obj._headers;
		this->_charParsed = obj._charParsed;
		this->_body = obj._body;
		this->_isReqReceived = obj._isReqReceived;
	}
	return (*this);
}

void HttpRequest::readReceived(int clientSocket, int serverSocket)
{
	std::vector<char> buffer(BUFFER_SIZE);
	ssize_t bytes;

	if (clientSocket > -1 && serverSocket > -1)
	{
		while ((bytes = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0)) == 
				BUFFER_SIZE)
			this->_raw.append(buffer.data(), bytes);
		if (bytes == -1)
		{
			this->_raw.clear();
			throw SocketReadException();
		}
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
		return;
	}
}

bool HttpRequest::isBadRequest() const
{
	return (this->_isBadRequest);
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
		if (this->_isBadRequest)
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
		if (this->_isBadRequest)
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
		this->_isBadRequest = true;
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
		this->_isBadRequest = true;
		return ;
	}

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
	{
		this->_isBadRequest = true;
		return ;
	}
	name = normalizeHeaderName(name);

	if (name == "host" && this->_headers.find(name) != this->_headers.end())
	{
		this->_isBadRequest = true;
		return;
	}

	this->_headers[name] = value;
}

bool HttpRequest::canBeValidMethod(std::string &method)
{
	std::string::const_iterator it;
	for (it = method.begin(); it != method.end(); ++it) 
	{
		if (!std::isupper(*it))
			return (false);
	}
	return (true);
}

bool HttpRequest::canBeValidPath(std::string &path)
{
	
	if (*path.begin() != '/')
		return (false);
	std::string::const_iterator it;
	for (it = path.begin(); it != path.end(); ++it) 
	{
		bool isCharValid = std::isalnum(*it);

		for (size_t i = 0; i < strlen(ALLOWED_URI_SPECIALS); i++)
		{
			if (*it == ALLOWED_URI_SPECIALS[i])
				isCharValid = true;
		}
		if (!isCharValid)
			return (false);
	}
	return (true);
}

bool HttpRequest::canBeValidHttpProtocol(std::string &httpVersion)
{
	if (httpVersion.rfind("HTTP/", 0) == std::string::npos)
		return (false);
	return (true);
}

bool HttpRequest::isHeaderNameValid(std::string &name)
{
	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
	{
		if (!std::isalnum(*it) && *it != '-' && *it != '_' )
			return (false);
	}
	return (true);
}

bool HttpRequest::isHeaderValueValid(std::string &value)
{
	std::string::const_iterator it;
	for (it = value.begin(); it != value.end(); ++it) 
	{
		bool isCharValid = std::isalnum(*it);

		for (size_t i = 0; i < strlen(ALLOWED_HEADER_VAL); i++)
		{
			if (*it == ALLOWED_URI_SPECIALS[i])
				isCharValid = true;
		}
		if (!isCharValid)
			return (false);
	}
	return (true);
}

std::string HttpRequest::normalizeHeaderName(std::string &name)
{
	std::string normalized = "";

	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
		normalized.push_back(std::tolower(*it));
	return (normalized);
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