/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/22 10:09:52 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() :  _raw(""), _receivedCount(0), _lineParsed(0),
	_isBadRequest(false), _method(""), _uri(""), _httpVersion("") {}

HttpRequest::HttpRequest(const HttpRequest &obj) : _raw(""), _receivedCount(0), 
	_lineParsed(0), _isBadRequest(false), _method(""), _uri(""), 
	_httpVersion("")
{
	*this = obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		this->_raw = obj._raw;
		this->_receivedCount = obj._receivedCount;
		this->_lineParsed = obj._lineParsed;
		this->_isBadRequest = obj._isBadRequest;
		this->_headers = obj._headers;
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
		std::cout << this->_raw << "size = " << this->_raw.size() << " Last content = " << (int)buffer[bytes - 2] << " " << (int)buffer[bytes - 1] << std::endl;
		this->_receivedCount++;
		parseRaw();
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
	if (pos != std::string::npos && this->_lineParsed == 0)
	{
		line = _raw.substr(0, pos);
		parseStartLine(line);
		this->_lineParsed++;
		if (this->_isBadRequest)
			return ;
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
	std::cout << "Start line correct with METHOD = \"" << this->_method 
			  << "\" URI = \"" << this->_uri << "\" HTTP VERSION = \"" 
			  << this->_httpVersion << "\"" <<  std::endl;
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

// Exceptions
const char * HttpRequest::SocketReadException::what()
{
	return ("Read Exception");
}

const char * HttpRequest::RawUninitializedException::what()
{
	return ("Raw unitialized exception");
}