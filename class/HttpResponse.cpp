/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 14:26:05 by fdehan           ###   ########.fr       */
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
	   << getStrStatusCode(this->_statusCode) << "\r\n"
	   << "\r\n"
	   << this->_body;
	
	this->_raw = ss.str();
	this->_isEncoded = true;
}