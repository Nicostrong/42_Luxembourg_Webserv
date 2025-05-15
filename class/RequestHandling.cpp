/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/15 09:23:31 by fdehan           ###   ########.fr       */
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
	const Directive*		redirectDirective;

	try
	{
		if (req.getStatusCode() == BAD_REQUEST)
		{
			getErrorResponse(BAD_REQUEST, server, req, resp);
			return ;
		}

		loc = server.getMatchingLoc(req.getUri());
		req.setLocation(loc);

		if (!req.getLocation())
		{
			getErrorResponse(NOT_FOUND, server, req, resp);
			return ;
		}

		if (!loc->getMethod()->isAllowed(req.getMethod()))
		{
			getErrorResponse(METHOD_NOT_ALLOWED, server, req, resp);
			return ;
		}
		
		redirectDirective = loc->findDirective("return");

		if (redirectDirective)
		{
			handleRedirect(redirectDirective, req, resp);
			return ;
		}
		
		cgiDirectives = loc->findDirectives("cgi");
		
		if (cgiDirectives.size() > 0)
		{
			handleCGI(cgiDirectives, server, req, resp);
			return ;
		}

		realPath = Uri::buildRealAbsolute(server, loc, req.getUri());
		req.setPathTranslated(realPath);
		//Should handle normally not cgi



		getErrorResponse(OK, server, req, resp);
	}
	catch(const std::exception& e)
	{
		getErrorResponse(INTERNAL_SERVER_ERROR, server, req, resp);
	}
}


void RequestHandling::handleCGI(const std::list<Directive*>& cgiDirectives, 
	Server& server, const HttpRequest& req, HttpResponse& resp)
{
	std::string cgiPath = Uri::getCgiPath(cgiDirectives, req.getLocation(), req.getUri());
	if (cgiPath.empty())
	{
		getErrorResponse(NOT_FOUND, server, req, resp);
		return ;
	}
	std::string realCgiPath = Uri::buildRealRelative(server, req.getLocation(), cgiPath);
	LOG_DEB("CGI script: " + realCgiPath);

	if (!isFileReadable(server, req, resp, realCgiPath))
		return ;
	
	getErrorResponse(OK, server, req, resp);
}

void RequestHandling::handleRedirect(const Directive* redirectDirective, HttpResponse& resp)
{
	resp.setStatusCode(FOUND);
	resp.addHeader("Location", redirectDirective->getValue());
	resp.setAsComplete();
}
void RequestHandling::handleDirctoryListing(const HttpRequest& req, HttpResponse& resp)
{
	
}

bool RequestHandling::isFileReadable(Server& server, const HttpRequest& req, 
	HttpResponse& resp, const std::string& path)
{
	struct stat infos;

	if (stat(path.c_str(), &infos) == -1)
	{
		if (errno == ENOENT)
		{
			getErrorResponse(NOT_FOUND, server, req, resp);
			return (false);
		}
		throw std::runtime_error("Stat failed");
	}

	if (!S_ISREG(infos.st_mode))
	{
		getErrorResponse(NOT_FOUND, server, req, resp);
		return (false);
	}

	if (access(path.c_str(), R_OK) == -1)
	{
		getErrorResponse(FORBIDDEN, server, req, resp);
		return (false);
	}
		
	return (true);
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
	resp.setStatusCode((HttpBase::HttpCode)statusCode);
	
	try
	{
		std::string customErrorPath = server.getPathError(statusCode);
		Ressource 	errorRessource(customErrorPath);
		
		if (errorRessource.isFail())
		{
			LOG_ERROR("Failed to load custom error response");
			throw std::runtime_error("Failed to load custom error response");
		}
		else
		{
			resp.setBody(errorRessource.getRaw());
			resp.setAsComplete();
		}
	}
	catch(const std::exception& e)
	{
		resp.setBody(
			HttpBase::getDefaultErrorPage((HttpBase::HttpCode)statusCode));
		resp.setAsComplete();
	}
	
	(void)req;
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