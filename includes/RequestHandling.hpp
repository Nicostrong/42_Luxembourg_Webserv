/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 13:38:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLING_HPP
#define REQUEST_HANDLING_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"

class RequestHandling
{
	public:
		RequestHandling(const RequestHandling& obj);
		~RequestHandling();
		RequestHandling& 		operator=(const RequestHandling& obj);
		static HttpResponse&	getResponse(Server& server, 
			const HttpRequest& req);
		
	private:
		RequestHandling();
		static void getErrorResponse(Server& server, 
			const HttpRequest& req, HttpResponse& resp);
};

#endif