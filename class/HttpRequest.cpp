/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 12:45:34 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() : _isValid(false), _rawInit(false), _raw("") {}

HttpRequest::HttpRequest(const HttpRequest &obj) 
{
	(void)obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
		(void)obj;
	return (*this);
}

HttpRequest *HttpRequest::decode(int clientSocket, int serverSocket)
{
	HttpRequest *httpReq = new HttpRequest();
	
	try
	{
		if (clientSocket > -1 && serverSocket > -1)
		{
			httpReq->readRaw(clientSocket, serverSocket);
			
		}
	}
	catch(const std::exception& e)
	{
		delete httpReq;
		throw e;
	}
	return (NULL);
}

void HttpRequest::readRaw(int clientSocket, int serverSocket)
{
	std::vector<char> buffer(BUFFER_SIZE);
	ssize_t bytes;
	
	if (clientSocket > -1 && serverSocket > -1)
	{
		while ((bytes = recv(clientSocket, buffer.data(), BUFFER_SIZE - 1, 0)) 
				== BUFFER_SIZE - 1)
		{
			buffer[bytes] = '\0';
			this->_raw.append(buffer.data());
		}
		if (bytes == -1)
		{
			this->_raw.clear();
			throw SocketReadException();
		}
		buffer[bytes] = '\0';
		this->_raw.append(buffer.data());
		std::cout << this->_raw << ", size = " << this->_raw.size() << std::endl;
		this->_rawInit = true;
		return ;
	}
	throw SocketReadException();
}

void HttpRequest::parseRaw()
{
	size_t pos;
	if (!this->_rawInit)
		throw RawUninitializedException();
	//Parse
	pos = this->_raw.find("\n");
	(void)pos;


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