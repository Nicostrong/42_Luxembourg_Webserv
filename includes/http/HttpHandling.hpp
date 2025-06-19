/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:34 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:19:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLING_HPP
# define HTTPHANDLING_HPP

#include "./../lib.hpp"
#include "./../handling/RequestHandling.hpp"
#include "./../handling/ResponseHandling.hpp"
#include "./../events/EventMonitoring.hpp"
#include "./../cgi/CgiParser.hpp"
#include "./../cgi/CgiResponseHandling.hpp"
#include "./../cgi/CgiResponse.hpp"
#include "./HttpParser.hpp"
#include "./HttpExceptions.hpp"
#include "./HttpSevereExceptions.hpp"

class Socket;

class HttpHandling
{
	public:
		HttpHandling();
		~HttpHandling();
		void	onRead(EventMonitoring& em, Socket* sock);
		void	onWrite(EventMonitoring& em, Socket* sock);
		void	setBodyRequired();
		void 	reset();
	private:
		HttpHandling(HttpHandling& obj);
		HttpHandling operator=(const HttpHandling& obj);

		void	setConnectionClose(Socket& sock);
		
		HttpParser			_parser;
		CgiParser			_cgiHandler;
		ResponseHandling	_resHandling;
		CgiResponse			_cgiResp;
};

#endif