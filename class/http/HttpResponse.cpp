/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 09:13:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpResponse.hpp"

HttpResponse::HttpResponse() : HttpBase(), _respType(UNKNOWN), 
	_headBuffer(HEAD_BSIZE)
	{}

HttpResponse::HttpResponse(const HttpResponse& obj) : HttpBase(obj), _headBuffer(0)
{
	*this = obj;
}

HttpResponse::~HttpResponse() {}

HttpResponse& HttpResponse::operator=(const HttpResponse& obj)
{
	if (this != &obj)
	{
		HttpBase::operator=(obj);
		this->_respType = obj._respType;
		this->_headBuffer = obj._headBuffer;
	}
	return (*this);
}

void HttpResponse::sendHead(Buffer& buff)
{
	std::stringstream ss;
	std::string 	  head;

	addHeader("Server", SERVER_VER);
	addHeader("Date", formatTimeHeader(time(NULL)));
	ss << "HTTP/1.1 " << this->_statusCode << " " 
	   << (this->_statusStr.size() ? 
	   	   this->_statusStr : getStrStatusCode(this->_statusCode)) << CRLF
	   << getHeaders_raw()
	   << CRLF;

	head = ss.str();
	if (head.size() > buff.getBufferUnused())
		throw HttpExceptions(INTERNAL_SERVER_ERROR);
	std::copy(head.begin(), head.end(), buff.beginUnused());
	buff.setBufferUsed(head.size());
}

void  HttpResponse::sendDefaultErrorPage(Buffer& buff)
{
	std::ostringstream oss;
	std::string	errorPage;
	std::string strStatusCode = getStrStatusCode(this->_statusCode);
	
	oss << "<html>" << CRLF
		<< "<head><title>" << this->_statusCode << " " << strStatusCode
		<< "</title></head>" << CRLF
		<< "<body>" << CRLF
		<< "<center><h1>" << this->_statusCode << " " << strStatusCode
		<< "</h1></center>" << CRLF
		<< "<hr>" << CRLF
		<< "<center>" << SERVER_VER << "</center>" << CRLF
		<< "</body>" << CRLF
		<< "</html>" << CRLF;
	errorPage = oss.str();
	addHeader("Content-Length", errorPage.size());
	addHeader("Content-Type", "text/html");
	sendHead(buff);
	if (buff.getBufferUnused() < errorPage.size())
		throw HttpExceptions(INTERNAL_SERVER_ERROR);
	std::copy(errorPage.begin(), errorPage.end(), buff.beginUnused());
	buff.setBufferUsed(errorPage.size());
}

void	HttpResponse::sendDirectoryListing(Buffer& buff, const HttpRequest& req)
{
	std::ostringstream oss;
	struct dirent* 	dirCont;
	std::string		cFile;
	std::string		fileName;
	std::string		relativeDir = Uri::getPathInfo(req.getLoc(), req.getUri());
	std::string 	directoryListingPage;

	DIR* dir = opendir(req.getPathTranslated().c_str());

	if (!dir)
		throw std::runtime_error("Failed to open directory");

	oss << "<html>" << CRLF
		<< "<head><title>Index of " << relativeDir << "</title></head>" << CRLF
		<< "<body>" << CRLF
		<< "<h1>Index of " << relativeDir 
		<< "</h1><hr><pre><a href=\"../\">../</a>" << CRLF;

	dirCont = readdir(dir);
	while (dirCont != NULL) 
	{
		formatIndividualFile(oss, req.getPathTranslated() + "/" + 
			dirCont->d_name, dirCont->d_name);
		dirCont = readdir(dir);
	}
	
	closedir(dir);
	oss	<< "</pre><hr></body>" << CRLF
		<< "</html>" << CRLF;

	directoryListingPage = oss.str();
	addHeader("Content-Length", directoryListingPage.size());
	addHeader("Content-Type", "text/html");
	sendHead(buff);
	if (buff.getBufferUnused() < directoryListingPage.size())
		throw std::runtime_error(
			"If DEFAULT error page is too big we cant do ANYTHING ;(");
	std::copy(directoryListingPage.begin(), directoryListingPage.end(), 
		buff.beginUnused());
	buff.setBufferUsed(directoryListingPage.size());
}

void HttpResponse::setStatusStr(const std::string& statusStr)
{
	this->_statusStr = statusStr;
}

void HttpResponse::setRespType(ResponseType type)
{
	this->_respType = type;
}

HttpResponse::ResponseType HttpResponse::getRespType() const
{
	return (this->_respType);
}
