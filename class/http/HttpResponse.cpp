/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:04:05 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpResponse.hpp"

HttpResponse::HttpResponse() : HttpParser(), _respType(UNKNOWN)
	{}

HttpResponse::HttpResponse(const HttpResponse& obj) : HttpParser(obj)
{
	*this = obj;
}

HttpResponse::~HttpResponse() {}

HttpResponse& HttpResponse::operator=(const HttpResponse& obj)
{
	if (this != &obj)
	{
		HttpParser::operator=(obj);
		this->_respType = obj._respType;
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
	   << getStrStatusCode(this->_statusCode) << CRLF
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


void HttpResponse::setRespType(ResponseType type)
{
	this->_respType = type;
}

HttpResponse::ResponseType HttpResponse::getRespType() const
{
	return (this->_respType);
}
