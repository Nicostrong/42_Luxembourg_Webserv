/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:36:17 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/05 09:49:20 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponse.hpp"

CgiResponse::CgiResponse() : _body(NULL), _contentLength(0), _errorCode(0), 
	_isEofReceived(false), _isProcessFinished(false), _isError(false), 
	_isEof(false), _isTe(false) {}


CgiResponse::~CgiResponse() 
{
	if (this->_body)
		delete this->_body;
}
bool CgiResponse::findHeader(const char* name)
{
	return (this->_headers.find(name) != this->_headers.end());
}

std::string& CgiResponse::findHeaderValue(const char* name)
{
	return (this->_headers.at(name));
}

const std::map<std::string, std::string>& CgiResponse::getHeaders() const
{
    return (this->_headers);
}

const std::list<std::string>& CgiResponse::getCookies() const
{
	return (this->_cookies);
}

bool CgiResponse::isError() const
{
	return (this->_isError);
}

size_t CgiResponse::getErrorCode() const
{
	return (this->_errorCode);
}

void CgiResponse::reset()
{
	this->_headers.clear();
	this->_cookies.clear();
	if (this->_body)
		delete this->_body;
	this->_body = NULL;
	this->_contentLength = 0;
	this->_errorCode = 0;
	this->_isEofReceived = false;
	this->_isProcessFinished = false;
	this->_isError = false;
	this->_isEof = false;
	this->_isTe = false;
	
}

CgiBody* CgiResponse::getBody()
{
	return (this->_body);
}

bool CgiResponse::isEof() const
{
	return (this->_isEof);
}

bool CgiResponse::isTE() const
{
	return (this->_isTe);
}

size_t CgiResponse::getContentLength() const
{
	return (this->_contentLength);
}

bool CgiResponse::isEofReceived() const
{
	return (this->_isEofReceived);
}

bool CgiResponse::isProcessFinished() const
{
	return (this->_isProcessFinished);
}

void CgiResponse::setBody(CgiBody* body)
{
	this->_body = body;
}

void CgiResponse::setEof(bool state)
{
	this->_isEof = state;
}

void CgiResponse::setTe(bool state)
{
	this->_isTe = state;
}

void CgiResponse::setContentLenght(size_t len)
{
	this->_contentLength = len;
}

void CgiResponse::setEofReceived(bool state)
{
	this->_isEofReceived = state;
}

void CgiResponse::setProcessFinished(bool state)
{
	this->_isProcessFinished = state;
}

void CgiResponse::setError(bool state)
{
	this->_isError = state;
}

void CgiResponse::setErrorCode(size_t code)
{
	this->_errorCode = code;
}
