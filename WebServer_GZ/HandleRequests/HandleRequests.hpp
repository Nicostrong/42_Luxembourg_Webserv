/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:01 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/28 11:45:15 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUESTS_HPP
#define HANDLEREQUESTS_HPP

#include "../../includes/HttpRequest.hpp"
#include "../../includes/Server.hpp"
//#include "../../includes/HandleConfig.hpp"
#include "../HandleConfig/HandleConfig.hpp"

class HttpRequest;
class Server;
class HandleConfig;

class HandleRequests: public HttpRequest
{
/*std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;*/
	
	private:
		void chooseMethod(Server server);
		std::map<std::string, std::string> webconfMap;
		std::map<std::string, std::string> handledRequests;
	public:
		HandleRequests(const char *config);
		~HandleRequests();
		void LoadParsing(const char *config);
		void ExecuteRequest();
		void Get();
		void Post();
		void Delete();
		const std::string& getMethodRules(std::string type);
		const std::string& getMethod();
		const std::string& getURI();
		const std::string& getHttpVersion();
		const std::string& getBody();
};

#endif