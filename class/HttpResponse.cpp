/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/29 08:22:12 by fdehan           ###   ########.fr       */
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
	return;
	std::stringstream ss;
	ss << "HTTP/1.1 " << req.getStatusCode() << "Bad Request" << "\r\n";
	ss << "\r\n";
	ss << "Bad Request";
	
	this->_raw = ss.str();
	this->_isEncoded = true;
	//if (req.getStatusCode() >= 400)
	//{
		
	//}
}