/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 23:07:28 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() : _isValid(false), _rawInit(false), _raw(""), 
	_receivedCount(0), _lineParsed(0), _isBadRequest(false) {}

HttpRequest::HttpRequest(const HttpRequest &obj) : _isValid(false), 
	_rawInit(false), _raw(""), _receivedCount(0), _lineParsed(0), 
	_isBadRequest(false)
{
	*this = obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		this->_isValid = obj._isValid;
		this->_rawInit = obj._rawInit;
		this->_raw = obj._raw;
		this->_receivedCount = obj._receivedCount;
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

void HttpRequest::parseRaw()
{
	std::string line;
	size_t pos = this->_raw.find("\r\n");
	if (pos != std::string::npos && this->_lineParsed == 0)
	{
		line = _raw.substr(0, pos);
		parseStartLine(line);
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
	
	if (tokens.size() != 3)
	{
		this->_isBadRequest = true;
		return ;
	}

	std::cout << line << std::endl;
}

bool HttpRequest::isBadRequest() const
{
	return (this->_isBadRequest);
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