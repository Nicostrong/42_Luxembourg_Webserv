/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 08:46:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include "lib.hpp"
#include "HttpBase.hpp"
#include "Location.hpp"

#define BUFFER_SIZE 1024

class HttpRequest : public HttpBase
{
public:

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
	HttpRequest(const std::string& remoteIp);
	HttpRequest(const HttpRequest &obj);
	virtual 				~HttpRequest();
	HttpRequest&			operator=(const HttpRequest &obj);
	void					readReceived(int clientSocket);
	HttpCode 				getStatusCode() const;
	void					setLocation(const Location* const loc);
	void					setPathTranslated(const std::string& pathTranslated)
		;
	void					setQueryParams(const std::string& queryParams);
	void					setScriptLoc(const std::string& scriptLoc);
	void					setPathInfo(const std::string& pathInfo);
	const Location* 		getLocation() const;
	const std::string&		getPathTranslated() const;
	const std::string&		getQueryParams() const;
	const std::string&		getScriptLoc() const;
	const std::string&		getPathInfo() const;

private:
	void 					parseRaw();
	void					parseStartLine(std::string &line);
	void 					parseHeader(std::string &line);

	// Reading variables
	size_t			_charParsed;
	
	// Handling variables
	std::string		_remoteIp;
	const Location*	_loc;
	std::string		_pathTranslated;
	std::string		_queryParams;
	
	// CGI related
	std::string		_scriptLoc;
	std::string		_pathInfo;
};

#endif