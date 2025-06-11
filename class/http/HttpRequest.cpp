/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/11 09:54:47 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpRequest.hpp"

HttpRequest::HttpRequest() : _loc(NULL), _isTE(false), _contentLength(0), 
	_server(NULL), _body(NULL) {}

HttpRequest::HttpRequest(const std::string& remoteIp) : HttpBase(), 
	_remoteIp(remoteIp), _loc(NULL), _isTE(false), _contentLength(0), 
	_server(NULL), _body(NULL) {}

HttpRequest::HttpRequest(const HttpRequest &obj) : HttpBase(obj)
{
	*this = obj;
}

HttpRequest::~HttpRequest() 
{
	if (this->_body)
		delete this->_body;
}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		if (this->_body)
			delete this->_body;
		
		HttpBase::operator=(obj);
		this->_remoteIp = obj._remoteIp;
		this->_loc = obj._loc;
		this->_pathTranslated = obj._pathTranslated;
		this->_pathInfo = obj._pathInfo;
		this->_cgiScript = obj._cgiScript;
		this->_cgiPath = obj._cgiPath;
		this->_redirect = obj._redirect;
		this->_filePath = obj._filePath;
		this->_queryParams = obj._queryParams;
		this->_fileSize = obj._fileSize;
		this->_isTE = obj._isTE;
		this->_contentLength = obj._contentLength;
		this->_body = obj._body;
	}
	return (*this);
}


void HttpRequest::setLoc(const Location* const loc)
{
	this->_loc = loc;
}

void HttpRequest::setPathTranslated(const std::string& pathTranslated)
{
	this->_pathTranslated = pathTranslated;
}

void HttpRequest::setPathInfo(const std::string& pathInfo)
{
	this->_pathInfo = pathInfo;
}

void HttpRequest::setCgiScript(const std::string& cgiScript)
{
	this->_cgiScript = cgiScript;
}

void HttpRequest::setCgiPath(const std::string& cgiPath)
{
	this->_cgiPath = cgiPath;
}

void HttpRequest::setRedirect(const std::string& redirect)
{
	this->_redirect = redirect;
}

void HttpRequest::setFilePath(const std::string& filePath)
{
	this->_filePath = filePath;
}

void HttpRequest::setQueryParams(const std::string& queryParams)
{
	this->_queryParams = queryParams;
}

void HttpRequest::setFileSize(size_t fileSize)
{
	this->_fileSize = fileSize;
}

void HttpRequest::setContentLength(size_t length)
{
	this->_contentLength = length;
}
		
void HttpRequest::setTE(bool state)
{
	this->_isTE = state;
}

void HttpRequest::setServer(const Server& server)
{
	this->_server = &server;
}

void HttpRequest::setBody(Body *body)
{
	this->_body = body;
}

const std::string& HttpRequest::getRemotIp( void ) const
{
	return (this->_remoteIp);
}

const Location* HttpRequest::getLoc() const
{
	return (this->_loc);
}

const std::string& HttpRequest::getPathTranslated() const
{
	return (this->_pathTranslated);
}

const std::string& HttpRequest::getPathInfo() const
{
	return (this->_pathInfo);
}

const std::string& HttpRequest::getCgiScript() const
{
	return (this->_cgiScript);
}

const std::string& HttpRequest::getCgiPath() const
{
	return (this->_cgiPath);
}

const std::string& HttpRequest::getRedirect() const
{
	return (this->_redirect);
}

const std::string& HttpRequest::getFilePath() const
{
	return (this->_filePath);
}

const std::string& HttpRequest::getQueryParams() const
{
	return (this->_queryParams);
}

size_t HttpRequest::getFileSize() const
{
	return (this->_fileSize);
}

size_t HttpRequest::getContentLength() const
{
	return (this->_contentLength);
}

const Server* HttpRequest::getServer() const
{
	return (this->_server);
}

Body* HttpRequest::getBody() const
{
	return (this->_body);
}

bool HttpRequest::isTE() const
{
	return (this->_isTE);
}
