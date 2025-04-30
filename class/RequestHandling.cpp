/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/30 16:59:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RequestHandling.hpp"

RequestHandling::RequestHandling() {}

RequestHandling::RequestHandling(const RequestHandling& obj)
{
	(void)obj;
}

RequestHandling::~RequestHandling() {}

RequestHandling& RequestHandling::operator=(const RequestHandling& obj)
{
	(void)obj;
	return (*this);
}

HttpResponse& RequestHandling::getResponse(const Server& server, 
	const HttpRequest& req)
{
	HttpResponse resp;

	if (req.getStatusCode() != HttpBase::OK)
	{
		resp.setStatusCode(req.getStatusCode());
		getErrorResponse(server, req, resp);
	}
	return (resp);
}

void RequestHandling::getErrorResponse(const Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	
}