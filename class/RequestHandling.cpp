/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/02 07:19:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RequestHandling.hpp"

RequestHandling::RequestHandling() {}

RequestHandling::RequestHandling(const RequestHandling& obj): HttpBase()
{
	(void)obj;
}

RequestHandling::~RequestHandling() {}

RequestHandling& RequestHandling::operator=(const RequestHandling& obj)
{
	(void)obj;
	return (*this);
}

void RequestHandling::getResponse(Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	if (!req.isReceived())
		return ;
	//if (req.getStatusCode() != HttpBase::OK)
	//{
	resp.setStatusCode(req.getStatusCode());
	resp.setMethod(req.getMethod());
	resp.setUri(req.getUri());
	resp.setBody(req.getBody());
	resp.setHTTP(req.getHTTP());
	getErrorResponse(server, req, resp);
	//}
}

void RequestHandling::getErrorResponse(Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	(void)req;
	const std::string path = server.getPathError(resp.getStatusCode());

	server.getRessourcesManager().loadRessource(path);
	
	Ressource::State rState = 
				server.getRessourcesManager().getRessourceState(path);

	if (rState == Ressource::ERROR)
	{
		resp.setBody(
				HttpBase::getDefaultErrorPage(resp.getStatusCode()));
		resp.setAsComplete();
	}
	else if (rState == Ressource::RECEIVED)
	{
		resp.setBody(
				server.getRessourcesManager().getRessource(path)->getRaw());
		resp.setAsComplete();
	}
}

// ########################################
// GZ - ADDED FUNCTIONS FROM HANDLEREQUESTS
// ########################################

bool RequestHandling::_checkMethod(Server server)
{
	return (server.checkMethod(_uri, _method));
}

bool RequestHandling::_checkUri(Server server)
{
	return (server.checkUri(_uri));
}