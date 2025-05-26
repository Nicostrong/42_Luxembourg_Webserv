/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 11:33:55 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "./lib.hpp"
#include "./HttpBase.hpp"
#include "./HttpParser.hpp"
#include "./server/Location.hpp"
#include "./MemoryPool.hpp"
#include "./StartLine.hpp"
#include "./Headers.hpp"

class HttpRequest : public HttpParser
{
	public:

		HttpRequest();
		HttpRequest(const std::string& remoteIp);
		HttpRequest(const HttpRequest &obj);
		virtual 				~HttpRequest();
		HttpRequest&			operator=(const HttpRequest &obj);
		void					readReceived(int clientSocket);
		void					setLoc(const Location* const loc);
		void					setPathTranslated(
			const std::string& pathTranslated);
		void					setPathInfo(const std::string& pathInfo);
		void					setCgiScript(const std::string& cgiScript);
		void					setCgiPath(const std::string& cgiPath);
		void					setRedirect(const std::string& redirect);
		void					setFilePath(const std::string& filePath);
		void					setQueryParams(const std::string& queryParams);
		void					setFileSize(size_t fileSize);
		const Location* 		getLoc() const;
		const std::string&		getPathTranslated() const;
		const std::string&		getPathInfo() const;
		const std::string&		getCgiScript() const;
		const std::string&		getCgiPath() const;
		const std::string&		getRedirect() const;
		const std::string&		getFilePath() const;
		const std::string&		getQueryParams() const;
		size_t					getFileSize() const;
		void					onRead(int socket);
		

	private:
		
		// Handling variables
		std::string		_remoteIp;

		// handling
		const Location*	_loc;
		std::string		_pathTranslated;
		std::string		_pathInfo;
		std::string		_cgiScript;
		std::string		_cgiPath;
		std::string		_redirect;
		std::string		_filePath;
		std::string		_queryParams;
		size_t			_fileSize;

		//Requests parts

		StartLine	_sl;
		Headers		_headers;
};

#endif