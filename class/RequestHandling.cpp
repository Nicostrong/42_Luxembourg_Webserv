/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/12 11:04:34 by gzenner          ###   ########.fr       */
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

/*
 * Should clean this abomination but its 23h30 so.. not now
 * and getRealPath seems working, need to check if the path is valid and exist
 * and excute cgi if the location let it run.
 */
void RequestHandling::getResponse(Server& server, 
	HttpRequest& req, HttpResponse& resp)
{
	const Location* 		loc;
	std::string 			realPath;
	std::list<Directive*>	cgiDirectives;
	
	if (!req.isReceived())
		return ;

	if (req.getStatusCode() == BAD_REQUEST)
	{
		getErrorResponse(BAD_REQUEST, server, req, resp);
		return ;
	}

	loc = server.getUri(req.getUri());
	req.setLocation(loc);
	if (!req.getLocation())
	{
		getErrorResponse(NOT_FOUND, server, req, resp);
		return ;
	}
	std::cout << "hey" << std::endl;
	realPath = server.getRealPath(loc, req.getUri());
	req.setPathTranslated(realPath);
	cgiDirectives = loc->findDirectives("cgi");
	
	if (cgiDirectives.size() > 0)
	{
		handleCGI(cgiDirectives, server, req, resp);
		return ;
	}
	getErrorResponse(OK, server, req, resp);
}

void RequestHandling::handleCGI(const std::list<Directive*>& cgiDirectives, 
	Server& server, const HttpRequest& req, HttpResponse& resp)
{
	std::list<Directive*>::const_iterator it;

	for (it = cgiDirectives.begin(); it != cgiDirectives.end(); it++)
	{
		std::cout << (*it)->getValue(0) << std::endl;
		//if (req.getPathTranslated().find((*it)->getValue(0)) !)
			// Try to exec
	}
		(void)req;
		(void)server;
		(void)resp;
}

// See GZ/example_response.txt for example of response
// Explanations: This code concats a response similar to the on given in the textfile
// I wrote the Getters (specifically getHeaders_raw()) to return the values.
// Code is pretty self-explaining, getHeader returns a string containing all keys/values from _headers
// Research has told me the method and uri do NOT go into the Response!

std::string RequestHandling::buildHttpResponse(const HttpRequest& req, const HttpResponse& res)
{
    std::ostringstream response;
	response << req.getHTTP() << " " << req.getStatusCode() << " " << getReasonPhrase(req.getStatusCode()) << CRLF;
    response << res.getHeaders_raw() << CRLF;
    response << "Content-Length: " << req.getBody().size() << CRLF;
    response << "Connection: close\r\n";
    response << CRLF; // Blank line to separate headers from body
    response << req.getBody();
	//std::cout << "[debug response]:\n" << response << "\n";
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

void RequestHandling::getErrorResponse(int statusCode, Server& server, 
	const HttpRequest& req, HttpResponse& resp)
{
	(void)req;
	resp.setStatusCode((HttpBase::HttpCode)statusCode);
	Ressource err(server.getPathError(statusCode));
	
	if (err.isFail())
		LOG_ERROR("Failed to load custom error response");
	else
	{
		resp.setBody(err.getRaw());
		resp.setAsComplete();
		return ;
	}
	resp.setBody(
		HttpBase::getDefaultErrorPage((HttpBase::HttpCode)statusCode));
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