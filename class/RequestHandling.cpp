/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/06 21:27:04 by fdehan           ###   ########.fr       */
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
	resp.setStatusCode(req.getStatusCode());
	if (req.getStatusCode() != BAD_REQUEST)
	{
		if (!server.checkUri(req.getUri()))
			resp.setStatusCode(NOT_FOUND);
	}
	
	//if (req.getStatusCode() != HttpBase::OK)
	//{
	/*
	resp.setBody(req.getBody());
	resp.setHTTP(req.getHTTP());*/
	getErrorResponse(server, req, resp);
	//}
}

// See GZ/example_response.txt for example of response
// Explanations: This code concats a response similar to the on given in the textfile
// I wrote the Getters (specifically getHeaders()) to return the values.
// Code is pretty self-explaining, getHeader returns a string containing all keys/values from _headers
// Research has told me the method and uri do NOT go into the Response!

std::string RequestHandling::buildHttpResponse(const HttpRequest& req, const HttpResponse& res)
{
    std::ostringstream response;
	response << req.getHTTP() << " " << req.getStatusCode() << " " << getReasonPhrase(req.getStatusCode()) << "\r\n";
    response << res.getHeaders() << "\r\n";
    response << "Content-Length: " << req.getBody().size() << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n"; // Blank line to separate headers from body
    response << req.getBody();
	response << "\r\n"; // Blank line end
	std::cout << "[debug response]:\n" << response << "\n";
    return response.str();
}

std::string RequestHandling::getReasonPhrase(HttpCode code)
{
	switch (code)
	{
		case 200: return "OK";
		case 400: return "BAD REQUEST";
		case 500: return "INTERNAL SERVER ERROR";
		default: return "UNKNOWN";
	}
}

void RequestHandling::getErrorResponse(Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	(void)req;
	Ressource err(server.getPathError(resp.getStatusCode()));
	
	if (err.isFail())
		LOG_ERROR("Failed to load custom error response");
	else
	{
		resp.setBody(err.getRaw());
		resp.setAsComplete();
		return ;
	}
	resp.setBody(
		HttpBase::getDefaultErrorPage(resp.getStatusCode()));
	resp.setAsComplete();
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

bool RequestHandling::_checkHTTP()
{
	return (true);
}

bool RequestHandling::_checkBody()
{
	return (true);
}