/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:01 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/30 14:07:04 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUESTS_HPP
#define HANDLEREQUESTS_HPP

#include "../../includes/HttpRequest.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/HandleConfig.hpp"
#include "../../includes/IEventHandler.hpp"
#include "../../includes/EventMonitoring.hpp"
#include "../../includes/Ressource.hpp"
#include "../../includes/RessourcesManager.hpp"
#include "../../includes/RequestHandling.hpp"

#define BUFFER_SIZE 1024

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
		char buffer[1024];
		std::string totalBuffer;
		EventMonitoring& em;
		std::map<std::string, std::string> webconfMap;
		std::map<std::string, std::string> response;
	public:
		HandleRequests(EventMonitoring& ref);
		HandleRequests(const HandleRequests& copy);
		HandleRequests& operator=(const HandleRequests& copy);
		~HandleRequests();
		
		const std::map<std::string, std::string>& _getResponse(Server server);
		const std::string& _getMethod();
		const std::string& _getUri();
		const std::string& _getHttpVersion();
		const std::string& _getBody();
		
		bool _checkMethod(Server server);
		bool _checkUri(Server server);
};

#endif