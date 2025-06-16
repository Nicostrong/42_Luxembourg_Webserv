/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/16 18:49:05 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiParser.hpp"

CgiParser::CgiParser() 
{
    this->_headBuffer.reserve(CGI_HEAD_BUFF);
}

CgiParser::~CgiParser() {}

void	CgiParser::onRead(Buffer &buff, CgiResponse& cgiResponse)
{
    switch (this->_state)
	{
		case CGI_HEAD:
			if (!handleHeaders(buff, cgiResponse))
				return ;
		case CGI_HEAD_RECEIVED:
			//Receiving head
		default:
			break;
	}
}

void CgiParser::parseHeaders(CgiResponse& cgiResponse)
{
	size_t sPos = 2;
	size_t ePos = this->_headBuffer.find(CRLF, sPos);

	while (ePos != std::string::npos)
	{
		parseHeader(this->_headBuffer.substr(sPos, ePos - sPos), cgiResponse);
		sPos = ePos + 2;
		ePos = this->_headBuffer.find(CRLF, sPos);
	}
	
	if (this->_headBuffer.size())
		parseHeader(this->_headBuffer.substr(sPos), cgiResponse);
}

void CgiParser::parseHeader(const std::string& line, CgiResponse& cgiResponse)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
		throw HttpExceptions(HttpBase::BAD_GATEWAY);

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!HttpBase::isHeaderNameValid(name))
		throw HttpExceptions(HttpBase::BAD_GATEWAY);
	name = HttpBase::normalizeHeaderName(name);
	cgiResponse.addHeader(name, value);
}

bool CgiParser::handleHeaders(Buffer& buff, CgiResponse& cgiResponse)
{
	size_t len = std::min(buff.getBufferUnread(), 
				this->_headBuffer.capacity() - this->_headBuffer.size());

	this->_headBuffer.append(buff.getDataUnread(), len);
	
	size_t pos = this->_headBuffer.find(CRLF CRLF);

	if (pos == std::string::npos)
	{
		buff.setBufferRead(len);

		if (this->_headBuffer.size() >= this->_headBuffer.capacity())
			throw HttpExceptions(
				HttpBase::BAD_GATEWAY);
		return (false);
	}
	
	buff.setBufferRead(pos + len - this->_headBuffer.size() + 4);
	this->_headBuffer.erase(pos);

	parseHeaders(cgiResponse);
	if (this->_state == CGI_HEAD)
		this->_state = CGI_HEAD_RECEIVED;
	return (true);
}
