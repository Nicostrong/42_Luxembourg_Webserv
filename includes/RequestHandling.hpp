/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 14:08:07 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLING_HPP
#define REQUEST_HANDLING_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"
#include "Uri.hpp"
#include "HttpBase.hpp"
#include "CGI.hpp"
#include <string>
#include <sstream>

class RequestHandling: public HttpBase
{
	public:
		RequestHandling(const RequestHandling& obj);
		~RequestHandling();
		RequestHandling& operator=(const RequestHandling& obj);
		static void	getResponse(Server& server, HttpRequest& req, 
			HttpResponse& resp);
		std::string	buildHttpResponse(const HttpRequest& req, const HttpResponse& res);
		std::string getReasonPhrase(HttpCode code);
	private:
		RequestHandling();
		static void getErrorResponse(int statusCode, Server& server, const HttpRequest& req, 
			HttpResponse& resp);
		static void handleCGI(const std::list<Directive*>& cgiDirectives, 
			Server& server, const HttpRequest& req, HttpResponse& resp);
		static bool isFileReadable(Server& server, const HttpRequest& req, 
			HttpResponse& resp, const std::string& path);
		bool _checkMethod(Server server);
		bool _checkUri(Server server);
		bool _checkHTTP();
		bool _checkBody();
};

#endif