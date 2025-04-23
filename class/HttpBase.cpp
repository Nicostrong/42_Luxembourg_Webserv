/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:07:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/23 18:18:03 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpBase.hpp"

HttpBase::HttpBase() : _raw(""), _method(""), _uri(""), _httpVersion(""), 
	_body(""), _headers() {}

HttpBase::HttpBase(const HttpBase &obj) 
{
	*this = obj;
}

HttpBase::~HttpBase() {}

HttpBase &HttpBase::operator=(const HttpBase &obj) 
{
	if (this != &obj)
	{
		this->_raw = obj._raw;
		this->_method = obj._method;
		this->_uri = obj._uri;
		this->_httpVersion = obj._httpVersion;
		this->_body = obj._body;
		this->_headers = obj._headers;
	}
	return (*this);
}

bool HttpBase::canBeValidMethod(std::string &method)
{
	std::string::const_iterator it;
	for (it = method.begin(); it != method.end(); ++it) 
	{
		if (!std::isupper(*it))
			return (false);
	}
	return (true);
}

bool HttpBase::canBeValidPath(std::string &path)
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

bool HttpBase::canBeValidHttpProtocol(std::string &httpVersion)
{
	if (httpVersion.rfind("HTTP/", 0) == std::string::npos)
		return (false);
	return (true);
}

bool HttpBase::isHeaderNameValid(std::string &name)
{
	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
	{
		if (!std::isalnum(*it) && *it != '-' && *it != '_' )
			return (false);
	}
	return (true);
}

bool HttpBase::isHeaderValueValid(std::string &value)
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

std::string HttpBase::normalizeHeaderName(std::string &name)
{
	std::string normalized = "";

	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
		normalized.push_back(std::tolower(*it));
	return (normalized);
}