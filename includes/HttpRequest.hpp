/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/08 16:09:20 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST
#define HTTP_REQUEST
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <cstring>
#include <sstream>
#include <exception>
#include "HttpBase.hpp"

#define BUFFER_SIZE 1024

class HttpRequest : public HttpBase
{
public:
	enum HttpMethod
	{
		GET = 0,
		POST = 1,
		DELETE = 2,
		INVALID = 3,
	};

	class SocketReadException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class RawUninitializedException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	HttpRequest(const std::string& remoteIp, const std::string& remoteHost);
	HttpRequest(const HttpRequest &obj);
	virtual ~HttpRequest();
	HttpRequest&	operator=(const HttpRequest &obj);
	void			readReceived(int clientSocket);
	HttpCode 		getStatusCode() const;
	bool			isReceived() const;

private:
	void parseRaw();
	void parseStartLine(std::string &line);
	void parseHeader(std::string &line);

	size_t _charParsed;
	bool _isReceived;
	std::string	_pathTranslated;
	std::string _remoteIp;
	std::string	_remoteHost;
};

#endif