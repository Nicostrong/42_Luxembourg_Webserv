/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:27:09 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 10:53:08 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponseHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

void CgiResponseHandling::handleHeaders(Socket& sock)
{
	CgiResponse* cgiResp = &sock.getHandler().getCgiResponse();
	HttpResponse* resp = &sock.getResp();
	
	const std::map<std::string, std::string> headers = cgiResp->getHeaders();
	std::map<std::string, std::string>::const_iterator it;
	bool isStatusFound = false;
	
	for (it = headers.begin(); it != headers.end(); ++it)
	{
		std::string name = (*it).first;
		if (name == "STATUS")
		{
			if (isStatusFound)
				continue;
			isStatusFound = true;
			handleStatusHeader((*it).second, sock);
		}
		else if (name == "TRANSFER-ENCODING" || name == "CONTENT-LENGTH")
		{
			//Should know when data is completly received otherwise if none specified wait for EOF
		}
		else if (name == "DATE" || name == "SERVER" || name == "CONNECTION")
			continue;
		else
			resp->addHeader(name, (*it).second);
	}
	(void)sock;
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