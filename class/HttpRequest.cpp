/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/17 16:11:57 by fdehan           ###   ########.fr       */
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
		this->_pathTranslated = obj._pathTranslated;
		this->_remoteIp = obj._remoteIp;
		this->_loc = obj._loc;
		this->_pathTranslated = obj._pathTranslated;
		this->_queryParams = obj._queryParams;
		this->_scriptLoc = obj._scriptLoc;
		this->_pathInfo = obj._pathInfo;
	}
	return (*this);
}


void HttpRequest::setLocation(const Location* const loc)
{
	this->_loc = loc;
}

void HttpRequest::setPathTranslated(const std::string& pathTranslated)
{
	this->_pathTranslated = pathTranslated;
}

void HttpRequest::setQueryParams(const std::string& queryParams)
{
	this->_queryParams = queryParams;
}

void HttpRequest::setScriptLoc(const std::string& scriptLoc)
{
	this->_scriptLoc =scriptLoc;
}

void HttpRequest::setPathInfo(const std::string& pathInfo)
{
	this->_pathInfo = pathInfo;
}

const Location* HttpRequest::getLocation() const
{
	return (this->_loc);
}

const std::string& HttpRequest::getPathTranslated() const
{
	return (this->_pathTranslated);
}

const std::string& HttpRequest::getQueryParams() const
{
	return (this->_queryParams);
}

const std::string& HttpRequest::getScriptLoc() const
{
	return (this->_scriptLoc);
}

const std::string& HttpRequest::getPathInfo() const
{
	return (this->_pathInfo);
}
