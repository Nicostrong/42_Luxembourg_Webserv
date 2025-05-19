/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:02 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 11:18:04 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpResponse.hpp"
#include "../includes/Socket.hpp"

HttpResponse::HttpResponse() : HttpParser()
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
		this->_enc = obj._enc;
	}
	return (*this);
}

void HttpResponse::sendHead(Socket& ctx) const
{
	std::stringstream ss;
	
	ss << "HTTP/1.1 " << this->_statusCode << " " 
	   << getStrStatusCode(this->_statusCode) << CRLF
	   << getHeaders_raw()
	   << CRLF;
	
	sendData(ctx, ss.str());
}

void	HttpResponse::sendData(Socket& ctx, const std::vector<char>& buff, size_t n) const
{
	ctx.getRespBuffer().bufferize(buff, n);
}

void	HttpResponse::sendData(Socket& ctx, const std::string& buff) const
{
	std::vector<char> vBuff(buff.begin(), buff.end());
	sendData(ctx, vBuff, vBuff.size());
}

void	HttpResponse::flushData(Socket& ctx) const
{
	ctx.getRespBuffer().flush();
}
