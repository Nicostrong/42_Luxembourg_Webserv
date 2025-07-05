/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:27:09 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/05 09:52:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponseHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

void CgiResponseHandling::handleHeaders(Socket& sock)
{
	CgiParser* cgiPars = &sock.getHandler().getCgiParser();
	CgiResponse* cgiResp = &sock.getHandler().getCgiResponse();
	HttpResponse* resp = &sock.getResp();
	
	const std::map<std::string, std::string> headers = cgiResp->getHeaders();
	std::map<std::string, std::string>::const_iterator it;
	bool isStatusFound = false;
	bool mandatoryFound = false;
	bool isEofDelimiter = true;

	resp->setStatusCode(HttpBase::OK);
	for (it = headers.begin(); it != headers.end(); ++it)
	{
		std::string name = (*it).first;
		if (name == "Status")
		{
			if (isStatusFound)
				continue;
			isStatusFound = true;
			mandatoryFound = true;
			
			handleStatusHeader((*it).second, sock);
		}
		else if (name == "Location")
		{
			mandatoryFound = true;
			resp->addHeader(name, (*it).second);
			resp->setStatusCode(HttpBase::FOUND);
		}
		else if (name == "Content-Type")
		{
			mandatoryFound = true;
			resp->addHeader(name, (*it).second);
		}
		else if (name == "Transfer-Encoding")
		{
			isEofDelimiter = false;
			handleTE(sock);
		}
		else if (name == "Content-Length")
		{
			isEofDelimiter = false;
			handleContentLength(sock);
		}
		else if (name == "Date" || name == "Server" || name == "Connection")
			continue;
		else
			resp->addHeader(name, (*it).second);
	}
	
	if (!mandatoryFound)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);

	std::list<std::string>::const_iterator itCookie;

	for (itCookie = cgiResp->getCookies().begin(); 
			itCookie != cgiResp->getCookies().end(); ++itCookie)
	{
		resp->addHeader("Set-Cookie", *itCookie);
	}
	
	cgiResp->setEof(isEofDelimiter);
	cgiPars->setState(CgiParser::CGI_BODY);
}

void CgiResponseHandling::handleStatusHeader(const std::string& status, 
		Socket& sock)
{
	std::string codeStr;
	size_t pos = status.find(" ");

	codeStr = status.substr(0, pos);

	if (codeStr.size() != 3)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);

	if (codeStr.find_last_not_of("0123456789") != std::string::npos)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);

	int code = std::atoi(codeStr.c_str());

	if (code < 100 || code >= 600)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);
	
	HttpResponse* resp = &sock.getResp();

	resp->setStatusCode(static_cast<size_t>(code));
	if (pos != std::string::npos)
		resp->setStatusStr(status.substr(pos + 1));
}

void CgiResponseHandling::handleTE(Socket& sock)
{
	std::string value = sock.getHandler().getCgiResponse().findHeaderValue("Transfer-Encoding");
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (value != "chunked")
		throw HttpExceptions(HttpBase::NOT_IMPLEMENTED);
	
	sock.getHandler().getCgiResponse().setTe(true);
}

void CgiResponseHandling::handleContentLength(Socket& sock)
{
	std::string value = sock.getHandler().getCgiResponse().findHeaderValue("Content-Length");

	
	if (value.empty() || 
		value.find_first_not_of("0123456789") != std::string::npos)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);
	
	std::istringstream iss(value);
	size_t cl;
    iss >> cl;

	if (iss.fail())
		throw HttpExceptions(HttpBase::BAD_GATEWAY);
	
	sock.getHandler().getCgiResponse().setContentLenght(cl);
}

bool CgiResponseHandling::isLocationValid(const std::string& loc)
{
	/*if (std::find_if(loc.begin(), loc.end(), std::not1(std::ptr_fun(isprint)))  
		!= loc.end())
		return (false);*/
	(void)loc;
	return (true);
}

//https://datatracker.ietf.org/doc/html/rfc3875#section-1.4
/* Tocheck: Content-Type
			Location
*/