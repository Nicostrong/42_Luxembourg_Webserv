/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:01 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/25 16:54:45 by gzenner          ###   ########.fr       */
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
		Server server;
		bool checkMethod(Server server);
		bool checkUri(Server server);
		bool checkHttpVersion(Server server);
		bool checkBody(Server server);
		void chooseMethod(Server server);
	public:
		void LoadParsing();
		void ExecuteRequest();
		void Get();
		void Post();
		void Delete();
};

#endif