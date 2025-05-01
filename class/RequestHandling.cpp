/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 13:50:53 by fdehan           ###   ########.fr       */
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

HttpResponse& RequestHandling::getResponse(Server& server, 
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

void RequestHandling::getErrorResponse(Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	const std::string path = server.getPathError(resp.getStatusCode());

	if (path != "")
	{
		server.getRessourcesManager().loadRessource(path);
		if (server.getRessourcesManager().getRessourceState(path) == 
				Ressource::ERROR)
		{
			return ;
		}
			
	}
	
}