/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:36 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 18:16:14 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpParser.hpp"

HttpParser::HttpParser() : HttpBase() {}

HttpParser::HttpParser(const HttpParser& obj) : HttpBase(obj) {}

HttpParser::~HttpParser() {}

HttpParser& HttpParser::operator=(const HttpParser& obj)
{
	HttpBase::operator=(obj);
	return (*this);
}

void HttpParser::parse()
{
	std::string line;
	size_t pos;
	
	while ((pos = this->_raw.find("\r\n", this->_pos)) != std::string::npos)
	{
		line = _raw.substr(this->_pos, pos - this->_pos);
		if (this->_pos == 0)
			parseStartLine(line);
		else if (line.empty() && 
					this->_pos > 0 && 
					this->_headers.find("HOST") != this->_headers.end())
		{
			this->_pos = pos + 2;
			this->
			this->_statusCode = OK;
			this->_isComplete = true;
			return ;
		}
		else
			parseHeader(line);
		if (this->_isComplete)
				return ;
		this->_pos = pos + 2;
	}
}

void HttpParser::parseStartLine(std::string &line)
{
	std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;

	while (iss >> token) {
        tokens.push_back(token);
    }
	
	if (tokens.size() != 3 || !canBeValidMethod(tokens.at(0)) || 
		!canBeValidPath(tokens.at(1)) || !canBeValidHttpProtocol(tokens.at(2)))
	{
		this->_isComplete = true;
		return ;
	}

	size_t queryPos = tokens.at(1).find('?');


	this->_method = tokens.at(0);
	this->_uri = tokens.at(1).substr(0, queryPos);
	if (queryPos != std::string::npos)
		this->_queryParams = tokens.at(1).substr(queryPos + 1);
	this->_httpVersion = tokens.at(2);
}

void HttpParser::parseHeader(std::string &line)
{
	size_t sep = line.find(':');
	
	if (sep == std::string::npos || sep == 0)
	{
		this->_isComplete = true;
		return ;
	}

	int	folding = (line.size() - sep > 1) ? 
				  line.at(sep + 1) == ' ' || line.at(sep + 1) == '\t' : 0;
	std::string name = line.substr(0, sep);
	std::string value = line.substr(sep + folding + 1);

	if (!isHeaderNameValid(name))
	{
		this->_isComplete = true;
		return ;
	}
	name = normalizeHeaderName(name);

	if (name == "HOST" && this->_headers.find(name) != this->_headers.end())
	{
		this->_isComplete = true;
		return;
	}

	this->_headers[name] = value;
}

// Custom exceptions

const char * HttpParser::SocketReadException::what() const throw()
{
	return ("Read Exception");
}
