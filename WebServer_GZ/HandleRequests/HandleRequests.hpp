/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:01 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/28 08:40:25 by gzenner          ###   ########.fr       */
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

class HandleRequests: public HttpRequest, public Server
{
/*std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;*/
	
	private:
		void chooseMethod(Server server);
	public:
		/*HandleRequests();
		~HandleRequests();*/
		void LoadParsing();
		void ExecuteRequest();
		void Get();
		void Post();
		void Delete();
};

#endif