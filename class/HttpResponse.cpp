/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 22:58:01 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpResponse.hpp"

HttpResponse::HttpResponse() : HttpParser(), _isHeadersEnc(false), _dataSent(0)
	{}

HttpResponse::HttpResponse(const HttpResponse& obj)
{
	*this = obj;
}

HttpResponse::~HttpResponse() {}

HttpResponse& HttpResponse::operator=(const HttpResponse& obj)
{
	if (this != &obj)
	{
		HttpParser::operator=(obj);
		this->_rawHeaders = obj._rawHeaders;
		this->_isHeadersEnc = obj._isHeadersEnc;
		this->_dataSent = obj._dataSent;
		this->_enc = obj._enc;
	}
	return (*this);
}


bool HttpResponse::isHeadersEnc() const
{
	return (this->_isHeadersEnc);
}

const std::string& HttpResponse::getRawHeaders() const
{
	return (this->_rawHeaders);
}

void HttpResponse::encodeHeaders()
{
	if (!this->_isHeadersEnc)
		return ;
	std::stringstream ss;
	
	ss << "HTTP/1.1 " << this->_statusCode << " " 
	   << getStrStatusCode(this->_statusCode) << CRLF
	   << getHeaders_raw()
	   << "Content-Type: text/html" << CRLF
	   << "Content-Length: "<< this->_body.size() << CRLF
	   << CRLF;
	this->_rawHeaders = ss.str();
	this->_isHeadersEnc = true;
}

void HttpResponse::addChunk(std::vector<char>& buf, size_t n)
{
	this->_enc.encodeChunk(buf, n);
}

void HttpResponse::sendHeaders()
{
	
}
