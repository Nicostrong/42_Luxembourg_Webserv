/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/23 18:10:29 by fdehan           ###   ########.fr       */
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

#define BUFFER_SIZE 1024

class HttpRequest
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

	HttpRequest();
	HttpRequest(const HttpRequest &obj);
	~HttpRequest();
	HttpRequest &operator=(const HttpRequest &obj);
	void readReceived(int clientSocket, int serverSocket);
	bool isBadRequest() const;

private:
	void parseRaw();
	void parseStartLine(std::string &line);
	void parseHeader(std::string &line);
	

	size_t _charParsed;
	std::string _raw;
	std::string _method;
	std::string _uri;
	std::string _httpVersion;
	std::string _body;
	std::map<std::string, std::string> _headers;
	bool _isBadRequest;
	bool _isReqReceived;
};

#endif