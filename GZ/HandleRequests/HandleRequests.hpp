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
#define BUFFER_SIZE 1024

class HttpRequest;
class Server;
class HandleConfig;

class HandleRequests: public HttpRequest, public IEventHandler
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

		enum ParseState {
			METHOD_START,
			METHOD,
			URI_START,
			URI,
			VERSION_START,
			VERSION_H,
			VERSION_HT,
			VERSION_HTT,
			VERSION_HTTP,
			VERSION_SLASH,
			HEADER_KEY,
			HEADER_VALUE,
			BODY
		};
		
	public:
		HandleRequests(EventMonitoring& ref);
		HandleRequests(const HandleRequests& copy);
		HandleRequests& operator=(const HandleRequests& copy);
		~HandleRequests();
		
		const std::string& getMethod();
		const std::string& getURI();
		const std::string& getHttpVersion();
		const std::string& getBody();
		
		void passFdMonitoring(int fd);
		void onReadEvent(int fd, int type);
		void onWriteEvent(int fd, int type);
		void onCloseEvent(int fd, int type);

		ParseResult parse(std::string& raw, Request& req);
		void HandleRequests::_buildResponse(int fd);
};

#endif