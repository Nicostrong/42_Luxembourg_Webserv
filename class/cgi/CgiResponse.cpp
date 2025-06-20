/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:36:17 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 15:08:28 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponse.hpp"

CgiResponse::CgiResponse() : _body(NULL), _isEof(false), _isTe(false), _contentLength(0) {}


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

void CgiResponse::reset()
{
	this->_headers.clear();
	if (this->_body)
		delete this->_body;
	this->_body = NULL;
	this->_isEof = false;
	this->_isTe = false;
	this->_contentLength = 0;
}

CgiBody* CgiResponse::getBody()
{
	return (this->_body);
}

bool CgiResponse::isEof() const
{
	return (this->_isEof);
}

bool CgiResponse::isTe() const
{
	return (this->_isTe);
}

size_t CgiResponse::getContentLenght() const
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
