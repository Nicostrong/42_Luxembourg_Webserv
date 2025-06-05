/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:19:58 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "./../lib.hpp"
#include "./../server/Server.hpp"
#include "./../server/Location.hpp"
#include "./HttpBase.hpp"
#include "./HttpParser.hpp"

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
		void					setContentLength(size_t length);
		void					setTE(bool state);
		void					setServer(const Server& server);
		const Location* 		getLoc() const;
		const std::string&		getPathTranslated() const;
		const std::string&		getPathInfo() const;
		const std::string&		getCgiScript() const;
		const std::string&		getCgiPath() const;
		const std::string&		getRedirect() const;
		const std::string&		getFilePath() const;
		const std::string&		getQueryParams() const;
		size_t					getFileSize() const;
		size_t					getContentLength() const;
		const Server*			getServer() const;
		bool					isTE() const;
		
		
		

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

		//Request Body
		bool			_isTE;
		size_t			_contentLength;

		// Server config
		const Server*			_server;
		
};

#endif