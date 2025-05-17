/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/17 11:45:12 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLING_HPP
# define REQUEST_HANDLING_HPP

# include "./lib.hpp"
# include "./Uri.hpp"
# include "./CGI.hpp"
# include "./HttpBase.hpp"
# include "./HttpRequest.hpp"
# include "./HttpResponse.hpp"
# include "./server/Server.hpp"

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
		static void handleRedirect(const Directive* redirectDirective, 
			HttpResponse& resp);
		static void handleDirctoryListing(const HttpRequest& req, 
			HttpResponse& resp);
		static void handleFileServing(Server& server, const HttpRequest& req, 
			HttpResponse& resp);
		static bool isFileReadable(Server& server, const HttpRequest& req, 
			HttpResponse& resp, const std::string& path);
		bool _checkMethod(Server server);
		bool _checkUri(Server server);
		bool _checkHTTP();
		bool _checkBody();
};

#endif