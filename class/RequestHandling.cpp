/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 22:43:00 by fdehan           ###   ########.fr       */
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
void RequestHandling::handleHeaders(Socket& sock)
{
	try
	{
		if (sock.getReq().getState() == HttpParser::HTTP_INVALID)
		{
			sock.getResp().setStatusCode(BAD_REQUEST);
			sock.getResp().setRespType(HttpResponse::ERROR);
			return ;
		}

		sock.getReq().setLoc(
			sock.getCtx().getMatchingLoc(sock.getReq().getUri()));

		if (!sock.getReq().getLoc())
		{
			sock.getResp().setStatusCode(NOT_FOUND);
			sock.getResp().setRespType(HttpResponse::ERROR);
			return ;
		}

		if (!sock.getReq().getLoc()->getMethod()->isAllowed(
			sock.getReq().getMethod()))
		{
			sock.getResp().setStatusCode(METHOD_NOT_ALLOWED);
			sock.getResp().setRespType(HttpResponse::ERROR);
			return ;
		}

		if (isRedirect(sock))
			return ;
		
		if (isCGI(sock))
			return ;
		
		sock.getReq().setPathTranslated(
			Uri::buildRealAbsolute(sock.getCtx(), sock.getReq().getLoc(), 
				sock.getReq().getUri()));

		if (isIndexFile(sock))
			return ;

		if (isDirctoryListing(sock))
			return ;
		
		if (isStaticFile(sock))
			return ;
		throw std::runtime_error("No match found");
	}
	catch(const std::exception& e)
	{
		sock.getResp().setStatusCode(INTERNAL_SERVER_ERROR);
		sock.getResp().setRespType(HttpResponse::ERROR);
	}
}


bool RequestHandling::isCGI(Socket& sock)
{
	const std::list<Directive*> cgiDirectives = 
			sock.getReq().getLoc()->findDirectives("cgi");

	if (cgiDirectives.size() < 1)
		return (false);

	// CGI METHODOLOGY NOT CORRECT

	return (false);

	/*std::string cgiPath = Uri::getCgiPath(cgiDirectives, req.getLocation(), req.getUri());
	if (cgiPath.empty())
	{
		getErrorResponse(NOT_FOUND, server, req, resp);
		return ;
	}
	std::string realCgiPath = Uri::buildRealRelative(server, req.getLocation(), cgiPath);
	LOG_DEB("CGI script: " + realCgiPath);

	if (!isFileReadable(server, req, resp, realCgiPath))
		return ;
	
	getErrorResponse(OK, server, req, resp);*/
}

bool RequestHandling::isStaticFile(Socket& sock)
{
	if (sock.getReq().getUri().size() && 
		*sock.getReq().getUri().rbegin() == '/')
		return (false);

	struct stat infos;
	
	if (stat(sock.getReq().getUri().c_str(), &infos) == -1)
	{
		if (errno != ENOENT)
			throw std::runtime_error("Stat failed");
		sock.getResp().setStatusCode(NOT_FOUND);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}

	if (S_ISDIR(infos.st_mode))
	{
		sock.getReq().setRedirect(sock.getReq().getUri() + "/");
		sock.getResp().setStatusCode(MOVED_PERMANENTLY);
		sock.getResp().setRespType(HttpResponse::REDIRECT);
		return (true);
	}
	
	if (!S_ISREG(infos.st_mode))
	{
		sock.getResp().setStatusCode(NOT_FOUND);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}

	if (access(sock.getReq().getUri().c_str(), R_OK) == -1)
	{
		sock.getResp().setStatusCode(FORBIDDEN);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}
	sock.getReq().setFilePath(sock.getReq().getUri());
	sock.getReq().setFileSize(infos.st_size);
	sock.getResp().setStatusCode(OK);
	sock.getResp().setRespType(HttpResponse::STATIC_FILE);
	return (true);
}

bool RequestHandling::isRedirect(Socket& sock)
{
	const Directive* redirectDirective = 
		sock.getReq().getLoc()->findDirective("return");

	if (!redirectDirective)
		return (false);
	sock.getReq().setRedirect(redirectDirective->getValue());
	sock.getResp().setStatusCode(FOUND);
	sock.getResp().setRespType(HttpResponse::REDIRECT);
	return (true);
}

bool RequestHandling::isIndexFile(Socket& sock)
{
	if (sock.getReq().getUri().size() && 
		*sock.getReq().getUri().rbegin() != '/')
		return (false);
	
	std::string str = sock.getCtx().getLocIndex(
		sock.getReq().getLoc());
	
	struct stat infos;
	std::string indexPath = Uri::buildUri(
			sock.getReq().getPathTranslated(), str);

	if (stat(indexPath.c_str(), &infos) == -1)
	{
		if (errno != ENOENT)
			throw std::runtime_error("Stat failed");
		return (false);
	}

	if (!S_ISREG(infos.st_mode))
		return (false);

	if (access(indexPath.c_str(), R_OK) == -1)
	{
		sock.getResp().setStatusCode(FORBIDDEN);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}
	sock.getReq().setFilePath(indexPath);
	sock.getReq().setFileSize(infos.st_size);
	sock.getResp().setStatusCode(OK);
	sock.getResp().setRespType(HttpResponse::STATIC_FILE);
	return (true);
}

bool RequestHandling::isDirctoryListing(Socket &sock)
{
	if (sock.getReq().getUri().size() && *sock.getReq().getUri().rbegin() != '/')
		return (false);
	
	const Directive* directive = 
		sock.getReq().getLoc()->findDirective("autoindex");
	
	
	if (!directive || directive->getValue() != "on")
	{
		sock.getResp().setStatusCode(FORBIDDEN);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}
	sock.getReq().setPathTranslated(
		Uri::trimSlashEnd(sock.getReq().getPathTranslated()));
	struct stat infos;
	if (stat(sock.getReq().getPathTranslated().c_str(), &infos) == -1 ||
			!S_ISDIR(infos.st_mode))
	{
		if (errno != ENOENT)
			throw std::runtime_error("Stat failed");
		sock.getResp().setStatusCode(NOT_FOUND);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}

	if (access(sock.getReq().getPathTranslated().c_str(), R_OK) == -1)
	{
		sock.getResp().setStatusCode(FORBIDDEN);
		sock.getResp().setRespType(HttpResponse::ERROR);
		return (true);
	}
	sock.getResp().setStatusCode(OK);
	sock.getResp().setRespType(HttpResponse::DIRECTORY_LISTING);
	return (true);
}
