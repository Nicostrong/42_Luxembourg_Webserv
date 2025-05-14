/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 17:20:19 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpResponse.hpp"

HttpResponse::HttpResponse() : HttpBase(), _isEncoded(false), _isComplete(false) 
	{}

HttpResponse::HttpResponse(const HttpResponse &obj) : HttpBase(obj), 
	_isEncoded(false), _isComplete(false) {}

HttpResponse::~HttpResponse() {}

HttpResponse &HttpResponse::operator=(const HttpResponse &obj)
{
	if (this != &obj)
	{
		HttpBase::operator=(obj);
		this->_isEncoded = obj._isEncoded;
		this->_isComplete = obj._isComplete;
	}
	return (*this);
}

void HttpResponse::setAsComplete()
{
	this->_isComplete = true;	
}

bool HttpResponse::isComplete()
{
	return (this->_isComplete);
}

bool HttpResponse::isEncoded()
{
	return (this->_isEncoded);
}

void HttpResponse::encodeResponse()
{
	if (!this->_isComplete)
		return ;
	std::stringstream ss;
	ss << "HTTP/1.1 " << this->_statusCode << " " 
	   << getStrStatusCode(this->_statusCode) << CRLF
	   << getHeaders_raw()
	   << "Content-Type: text/html" << CRLF
	   << "Content-Length: "<< this->_body.size() << CRLF
	   << CRLF
	   << this->_body;
	
	this->_raw = ss.str();
	this->_isEncoded = true;
}