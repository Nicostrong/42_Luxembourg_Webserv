/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:07:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 16:07:39 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpBase.hpp"

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

const std::string& HttpBase::getRawBody() const
{
	return (this->_body);
}

void HttpBase::setRawBody(const std::string body)
{
	this->_body = body;
}

const std::string& HttpBase::getHttpVersion() const
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

bool HttpBase::findHeader(const char* name)
{
	return (this->_headers.find(name) != this->_headers.end());
}

std::string& HttpBase::findHeaderValue(const char* name)
{
	return (this->_headers.at(name));
}

std::string	HttpBase::getStrStatusCode(HttpCode statusCode)
{
	switch (statusCode)
	{
		case 100: return "Continue";
		case 101: return "Switching Protocols";
		case 102: return "Processing";
		case 103: return "Early Hints";
		case 200: return "OK";
		case 201: return "Created";
		case 202: return "Accepted";
		case 203: return "Non-Authoritative Information";
		case 204: return "No Content";
		case 205: return "Reset Content";
		case 206: return "Partial Content";
		case 207: return "Multi-Status";
		case 208: return "Already Reported";
		case 226: return "IM Used";
		case 300: return "Multiple Choices";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 303: return "See Other";
		case 304: return "Not Modified";
		case 305: return "Use Proxy";
		case 307: return "Temporary Redirect";
		case 308: return "Permanent Redirect";
		case 400: return "Bad Request";
		case 401: return "Unauthorized";
		case 402: return "Payment Required";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 406: return "Not Acceptable";
		case 407: return "Proxy Authentication Required";
		case 408: return "Request Timeout";
		case 409: return "Conflict";
		case 410: return "Gone";
		case 411: return "Length Required";
		case 412: return "Precondition Failed";
		case 413: return "Payload Too Large";
		case 414: return "URI Too Long";
		case 415: return "Unsupported Media Type";
		case 416: return "Range Not Satisfiable";
		case 417: return "Expectation Failed";
		case 418: return "I'm a Teapot";
		case 421: return "Misdirected Request";
		case 422: return "Unprocessable Entity";
		case 423: return "Locked";
		case 424: return "Failed Dependency";
		case 425: return "Too Early";
		case 426: return "Upgrade Required";
		case 428: return "Precondition Required";
		case 429: return "Too Many Requests";
		case 431: return "Request Header Fields Too Large";
		case 451: return "Unavailable For Legal Reasons";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Timeout";
		case 505: return "HTTP Version Not Supported";
		case 506: return "Variant Also Negotiates";
		case 507: return "Insufficient Storage";
		case 508: return "Loop Detected";
		case 510: return "Not Extended";
		case 511: return "Network Authentication Required";
		default: return "Internal Server Error";
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

		for (size_t i = 0; i < std::strlen(ALLOWED_HEADER_VAL); i++)
		{
			if (*it == ALLOWED_HEADER_VAL[i])
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
