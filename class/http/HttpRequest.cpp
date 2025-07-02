/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:23:39 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/02 09:45:52 by nfordoxc         ###   Luxembourg.lu     */
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

void HttpRequest::setExtension( const std::string& extension )
{
	this->_extension = extension;
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

const std::string& HttpRequest::getExtension() const
{
	return (this->_extension);
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

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream&	operator<<( std::ostream &out,  const HttpRequest& src_object )
{
	out	<< GREEN << "================= HTTP REQUEST DETAILS =================" << std::endl
		<< "Remote IP:"
		<< src_object.getRemotIp() << std::endl
		<< "Path translated: "
		<< src_object.getPathTranslated() << std::endl
		<< "Path info: "
		<< src_object.getPathInfo() << std::endl
		<< "CGI script: "
		<< src_object.getCgiScript() << std::endl
		<< "CGI path: "
		<< src_object.getCgiPath() << std::endl
		<< "Redirect: "
		<< src_object.getRedirect() << std::endl
		<< "File path: "
		<< src_object.getFilePath() << std::endl
		<< "Query params: "
		<< src_object.getQueryParams() << std::endl
		<< "File size: "
		<< src_object.getFileSize() << std::endl
		<< "Content lenght: "
		<< src_object.getContentLength() << std::endl;
	if (src_object.getLoc())
		out << *src_object.getLoc() << std::endl;
	else
		out << "Location empty" <<std::endl;
	out	<< GREEN << "=================== END HTTP REQUEST ==================" << RESET << std::endl;
	return (out);
}