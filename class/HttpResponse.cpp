/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/30 17:05:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpResponse.hpp"

HttpResponse::HttpResponse() : HttpBase(), _isEncoded(false) {}

HttpResponse::HttpResponse(const HttpResponse &obj) : HttpBase(obj), 
	_isEncoded(false) {}

HttpResponse::~HttpResponse() {}

HttpResponse &HttpResponse::operator=(const HttpResponse &obj)
{
	if (this != &obj)
	{
		HttpBase::operator=(obj);
		this->_isEncoded = obj._isEncoded;
	}
	return (*this);
}

bool HttpResponse::isEncoded()
{
	return (this->_isEncoded);
}

void HttpResponse::encodeResponse(const HttpRequest &req)
{
	std::stringstream ss;
	ss << "HTTP/1.1 " << this->_statusCode << "Bad Request" << "\r\n";
	ss << "\r\n";
	ss << this->_body;
	
	this->_raw = ss.str();
	this->_isEncoded = true;
	//if (req.getStatusCode() >= 400)
	//{
		
	//}
}