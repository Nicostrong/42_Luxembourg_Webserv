/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 18:40:38 by fdehan           ###   ########.fr       */
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
	(void)clientSocket;
	(void)serverSocket;
	/*HttpRequest *httpReq = new HttpRequest();
	
	try
	{
	}
	catch(const std::exception& e)
	{
		delete httpReq;
		throw e;
	}*/
	return (NULL);
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