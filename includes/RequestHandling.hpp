/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/09 10:38:26 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLING_HPP
#define REQUEST_HANDLING_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"
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
		bool _checkMethod(Server server);
		bool _checkUri(Server server);
		bool _checkHTTP();
		bool _checkBody();
};

#endif