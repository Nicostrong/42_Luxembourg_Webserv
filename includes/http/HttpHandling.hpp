/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:34 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/09 23:37:06 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLING_HPP
# define HTTPHANDLING_HPP

#include "./../lib.hpp"
#include "./../handling/RequestHandling.hpp"
#include "./../handling/ResponseHandling.hpp"
#include "./../events/EventMonitoring.hpp"
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
		void 	reset();
	private:
		HttpHandling(HttpHandling& obj);
		HttpHandling operator=(const HttpHandling& obj);

		void	setConnectionClose(Socket& sock);
		
		ResponseHandling	_resHandling;
};

#endif