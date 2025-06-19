/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:36:17 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:23:46 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponse.hpp"

CgiResponse::CgiResponse() {}


CgiResponse::~CgiResponse() {}

void CgiResponse::setCode(size_t code) 
{
	this->_strCode = code;
}

void CgiResponse::setCodeStr(const std::string& codeStr) 
{
	this->_strCode = codeStr;
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
	this->_code = 200;
	this->_strCode.clear();
	this->_headers.clear();
	if (this->_body)
		delete this->_body;
	this->_body = NULL;
}
