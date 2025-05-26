/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 11:42:17 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() {}

HttpRequest::HttpRequest(const std::string& remoteIp) : HttpParser(), 
	_remoteIp(remoteIp), _loc(NULL) {}

HttpRequest::HttpRequest(const HttpRequest &obj) : HttpParser(obj)
{
	*this = obj;
}

HttpRequest::~HttpRequest() {}

HttpRequest &HttpRequest::operator=(const HttpRequest &obj) 
{
	if (this != &obj)
	{
		HttpParser::operator=(obj);
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
		this->_sl = obj._sl;
		this->_headers = obj._headers;
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

void HttpRequest::onRead(int socket)
{
	if (this->_sl.getState() == StartLine::RECEIVING)
		this->_sl.read(socket);
	else if (this->_sl.getState() == StartLine::READY && this->_headers.getState() == Headers::RECEIVING)
		this->_headers.read(socket);
}
