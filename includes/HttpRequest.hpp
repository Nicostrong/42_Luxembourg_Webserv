/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 11:18:01 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include "./lib.hpp"
#include "./HttpBase.hpp"
#include "HttpParser.hpp"
#include "./server/Location.hpp"

class HttpRequest : public HttpParser
{
	public:

		HttpRequest();
		HttpRequest(const std::string& remoteIp);
		HttpRequest(const HttpRequest &obj);
		virtual 				~HttpRequest();
		HttpRequest&			operator=(const HttpRequest &obj);
		void					readReceived(int clientSocket);
		void					setLocation(const Location* const loc);
		void					setPathTranslated(const std::string& pathTranslated);
		void					setQueryParams(const std::string& queryParams);
		void					setScriptLoc(const std::string& scriptLoc);
		void					setPathInfo(const std::string& pathInfo);
		const Location* 		getLocation() const;
		const std::string&		getPathTranslated() const;
		const std::string&		getQueryParams() const;
		const std::string&		getScriptLoc() const;
		const std::string&		getPathInfo() const;

	private:
		
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