/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:07:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 15:45:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpBase.hpp"

HttpBase::HttpBase() : _raw(""), _method(""), _uri(""), _httpVersion(""), 
	_body(""), 	_statusCode(BAD_REQUEST), _headers() {}

HttpBase::HttpBase(const HttpBase& obj) 
{
	*this = obj;
}

HttpBase::~HttpBase() {}

HttpBase& HttpBase::operator=(const HttpBase& obj) 
{
	if (this != &obj)
	{
		this->_raw = obj._raw;
		this->_method = obj._method;
		this->_uri = obj._uri;
		this->_httpVersion = obj._httpVersion;
		this->_body = obj._body;
		this->_statusCode = obj._statusCode;
		this->_headers = obj._headers;
	}
	return (*this);
}

HttpBase::HttpCode HttpBase::getStatusCode() const
{
	return (this->_statusCode);
}

void HttpBase::setStatusCode(HttpBase::HttpCode status)
{
	this->_statusCode = status;
}

const std::string& HttpBase::getBody() const
{
	return (this->_body);
}

void HttpBase::setBody(const std::string body)
{
	this->_body = body;
}

const std::string& HttpBase::getRaw() const
{
	return (this->_raw);
}

void HttpBase::setRaw(const std::string raw)
{
	this->_raw = raw;
}

std::string	HttpBase::getStrStatusCode(HttpCode statusCode)
{
	switch (statusCode)
	{
		case OK:
			return ("OK");
		case BAD_REQUEST:
			return ("Bad Request");
		case INTERNAL_SERVER_ERROR:
			return ("Internal Server Error");
	default:
		return ("Internal Server Error");
	}
}

std::string  HttpBase::getDefaultErrorPage(HttpCode statusCode)
{
	std::ostringstream oss;
	std::string strStatusCode = getStrStatusCode(statusCode);
	
	oss << "<html>" << CRLF
		<< "<head><title>" << statusCode << " " << strStatusCode
		<< "</title></head>" << CRLF
		<< "<body>" << CRLF
		<< "<center><h1>" << statusCode << " " << strStatusCode
		<< "</h1></center>" << CRLF
		<< "<hr>" << CRLF
		<< "<center>WebServ</center>" << CRLF
		<< "</body>" << CRLF
		<< "</html>" << CRLF;
	return (oss.str());
}

bool HttpBase::canBeValidMethod(std::string& method)
{
	std::string::const_iterator it;
	for (it = method.begin(); it != method.end(); ++it) 
	{
		if (!std::isupper(*it))
			return (false);
	}
	return (true);
}

bool HttpBase::canBeValidPath(std::string& path)
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

bool HttpBase::canBeValidHttpProtocol(std::string& httpVersion)
{
	if (httpVersion.rfind("HTTP/", 0) == std::string::npos)
		return (false);
	return (true);
}

bool HttpBase::isHeaderNameValid(std::string& name)
{
	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
	{
		if (!std::isalnum(*it) && *it != '-' && *it != '_' )
			return (false);
	}
	return (true);
}

bool HttpBase::isHeaderValueValid(std::string& value)
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

std::string HttpBase::normalizeHeaderName(std::string& name)
{
	std::string normalized = "";

	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
		normalized.push_back(std::tolower(*it));
	return (normalized);
}