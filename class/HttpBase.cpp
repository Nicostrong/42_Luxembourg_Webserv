/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:07:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/27 10:55:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpBase.hpp"

HttpBase::HttpBase() : _raw(""), _method(""), _uri(""), _httpVersion(""), 
	_body(""), 	_statusCode(BAD_REQUEST), _headers(), _transferEncoding(false) 
	{}

HttpBase::HttpBase(const HttpBase& obj) 
{
	*this = obj;
}

HttpBase::~HttpBase() {}

HttpBase& HttpBase::operator=(const HttpBase& obj) 
{
	if (this != &obj)
	{
		this->_raw = obj._raw;
		this->_method = obj._method;
		this->_uri = obj._uri;
		this->_httpVersion = obj._httpVersion;
		this->_body = obj._body;
		this->_statusCode = obj._statusCode;
		this->_headers = obj._headers;
		this->_transferEncoding = obj._transferEncoding;
	}
	return (*this);
}


HttpBase::HttpCode HttpBase::getStatusCode() const
{
	return (this->_statusCode);
}

void HttpBase::setStatusCode(HttpBase::HttpCode status)
{
	this->_statusCode = status;
}

const std::string& HttpBase::getMethod() const
{
	return (this->_method);
}

void HttpBase::setMethod(std::string method)
{
	this->_method = method;
}

const std::string& HttpBase::getUri() const
{
	return (this->_uri);
}

void HttpBase::setUri(const std::string uri)
{
	this->_uri = uri;
}

const std::string& HttpBase::getBody() const
{
	return (this->_body);
}

void HttpBase::setBody(const std::string body)
{
	this->_body = body;
}

const std::string& HttpBase::getHTTP() const
{
	return (this->_httpVersion);
}

void HttpBase::setHTTP(const std::string httpVersion)
{
	this->_httpVersion = httpVersion;
}

const std::string& HttpBase::getRaw() const
{
	return (this->_raw);
}

void HttpBase::setRaw(const std::string raw)
{
	this->_raw = raw;
}

bool HttpBase::isComplete() const
{
	return (this->_isComplete);
}
void HttpBase::setAsComplete()
{
	this->_isComplete = true;
}

std::string	HttpBase::getStrStatusCode(HttpCode statusCode)
{
	switch (statusCode)
	{
		case 200: return ("OK");
		case 301: return ("Moved Permanently");
		case 302: return ("Found");
		case 400: return ("Bad Request");
		case 403: return ("Forbidden");
		case 404: return ("Not Found");
		case 405: return ("Method Not Allowed");
		case 414: return ("URI Too Long");
		case 500: return ("Internal Server Error");
	default:
		return ("Internal Server Error");
	}
}

std::string 	HttpBase::getHeaders_raw() const
{
	std::string result;
	std::map<std::string, std::string>::const_iterator it = _headers.begin();
	while(it != _headers.end())
	{
		result += it->first;
		result += ": ";
		result += it->second;
		result += CRLF;
		++it;
	}
	return (result);
}

const std::map<std::string, std::string>&	HttpBase::getHeaders() const
{
	return _headers;
}

bool HttpBase::canBeValidMethod(const std::string& method)
{
	std::string::const_iterator it;
	for (it = method.begin(); it != method.end(); ++it) 
	{
		if (!std::isupper(*it))
			return (false);
	}
	return (true);
}

bool HttpBase::canBeValidPath(const std::string& path)
{
	
	if (*path.begin() != '/')
		return (false);
	std::string::const_iterator it;
	bool flag = false;

	for (it = path.begin(); it != path.end(); ++it) 
	{
		bool isCharValid = std::isalnum(*it);

		for (size_t i = 0; i < strlen(ALLOWED_URI_SPECIALS); i++)
		{
			if (*it == ALLOWED_URI_SPECIALS[i])
				isCharValid = true;
		}
		if (!isCharValid)
			return (false);
		if (*it == '/')
		{
			if (flag)
				return (false);
			else
				flag = true;
		}
		else
			flag = false;
	}
	return (true);
}

bool HttpBase::canBeValidHttpProtocol(const std::string& httpVersion)
{
	if (httpVersion.rfind("HTTP/", 0) == std::string::npos)
		return (false);
	return (true);
}

bool HttpBase::isHeaderNameValid(const std::string& name)
{
	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
	{
		if (!std::isalnum(*it) && *it != '-' && *it != '_' )
			return (false);
	}
	return (true);
}

bool HttpBase::isHeaderValueValid(const std::string& value)
{
	std::string::const_iterator it;
	for (it = value.begin(); it != value.end(); ++it) 
	{
		bool isCharValid = std::isalnum(*it);

		for (size_t i = 0; i < strlen(ALLOWED_HEADER_VAL); i++)
		{
			if (*it == ALLOWED_URI_SPECIALS[i])
				isCharValid = true;
		}
		if (!isCharValid)
			return (false);
	}
	return (true);
}

std::string HttpBase::normalizeHeaderName(const std::string& name)
{
	std::string normalized;

	std::string::const_iterator it;
	for (it = name.begin(); it != name.end(); ++it) 
		normalized.push_back(std::toupper(*it));
	return (normalized);
}

std::string HttpBase::normalizeUri(const std::string& uri)
{
	std::string normalized;
	
	std::string::const_iterator it;
	for (it = uri.begin(); it != uri.end(); ++it) 
		normalized.push_back(std::tolower(*it));

	//Should treat % things
	return (normalized);
}

// Internal helpers

void HttpBase::formatIndividualFile(std::ostringstream& oss, 
	const std::string& filePath, std::string fileName)
{
	
	struct stat st;
	std::string	modifiedTime;
	std::string	truncFileName;
	std::string	fileSize = "-";

	if (*fileName.begin() == '.')
		return ;
	if (stat(filePath.c_str(), &st) == -1)
		throw std::runtime_error("Failed to get stats about file");
	
	if (S_ISDIR(st.st_mode) || S_ISREG(st.st_mode))
	{
		fileName.append((S_ISDIR(st.st_mode) ? "/" : ""));
		modifiedTime = formatTime(st.st_mtime);
		truncFileName = truncateString(fileName, 50, 47, "..&gt;");
		if (S_ISREG(st.st_mode))
			fileSize = convertFileSize(st.st_size);
		oss << "<a href=\"" 
				<< fileName << "\">" 
				<< truncFileName << "</a>"
				<< std::string(std::max(1, 51 - (int)truncFileName.size()), ' ')
				<< modifiedTime
				<< std::string(std::max(1, 37 - (int)modifiedTime.size() - 
					(int)fileSize.size()), ' ')
				<< fileSize << CRLF;
	}
}

std::string	HttpBase::formatTime(const time_t& time)
{
	struct tm* timeInfo = localtime(&time);
	std::vector<char> buf(80);

	std::strftime(buf.data(), buf.size(), "%d-%b-%Y %H:%M", timeInfo);
	return (buf.data());
}

std::string	HttpBase::formatTimeHeader(const time_t& time)
{
	struct tm* timeInfo = localtime(&time);
	std::vector<char> buf(80);

	std::strftime(buf.data(), buf.size(), "%a, %d %b %Y %H:%M:%S GMT", timeInfo
					);
	return (buf.data());
}

std::string	HttpBase::truncateString(std::string str, size_t n, size_t truncLen,
	const std::string& trString)
{
	if (str.size() <= n)
	 	return (str);
	return (str.substr(0, truncLen) + trString);
}

std::string HttpBase::convertFileSize(off_t size)
{
	std::stringstream ss;
	
	ss << size;
	return (ss.str());
}
