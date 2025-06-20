/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:36:17 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 09:06:52 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponse.hpp"

CgiResponse::CgiResponse() : _body(NULL) {}


CgiResponse::~CgiResponse() 
{
	if (this->_body)
		delete this->_body;
}
bool CgiResponse::findHeader(const char* name)
{
	return (this->_headers.find(name) != this->_headers.end());
}

std::string& CgiResponse::findHeaderValue(const char* name)
{
	return (this->_headers.at(name));
}

const std::map<std::string, std::string>& CgiResponse::getHeaders() const
{
    return (this->_headers);
}

void CgiResponse::reset()
{
	this->_headers.clear();
	if (this->_body)
		delete this->_body;
	this->_body = NULL;
}
