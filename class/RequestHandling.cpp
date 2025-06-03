/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 14:41:38 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RequestHandling.hpp"

std::map<std::string, RequestHandling::HandlerFunc> RequestHandling::_handlers =
	RequestHandling::initHandlers();

void RequestHandling::handleHeaders(Socket& sock)
{
	Server*	ctx = &sock.getCtx();
	HttpRequest* req = &sock.getReq();
	HttpResponse* resp = &sock.getResp();

	LOG_DEB(req->getUri());
	resp->addHeader("Content-Length", 0);
	resp->addHeader("Connection", "keep-alive");

	if (std::strcmp(req->getHttpVersion().c_str(), SUPPORTED_HTTPVER) != 0)
		throw HttpSevereExceptions(HTTP_VERSION_NOT_SUPPORTED);
	
	
	
	if (!MethodHTTP::isMethodImplemented(req->getMethod()))
	{
		LOG_DEB(req->getMethod());
		throw HttpExceptions(NOT_IMPLEMENTED);
	}

	req->setLoc(
		ctx->getMatchingLoc(req->getUri()));

	if (!req->getLoc())
		throw HttpExceptions(NOT_FOUND);

	if (!req->getLoc()->getMethod()->isAllowed(req->getMethod()))
		throw HttpExceptions(METHOD_NOT_ALLOWED);

	req->setPathTranslated(
			Uri::buildRealAbsolute(*ctx, req->getLoc(), req->getUri()));
	
	_handlers[req->getMethod()](sock);
}

void RequestHandling::handleBody(Socket& sock)
{
	//SHould handle everything else than upload
	HttpRequest* req = &sock.getReq();
	BodyParsing* body = req->getBody();
	HttpResponse* resp = &sock.getResp();
	std::string	path = req->getPathTranslated();
	
	if (!body)
		throw HttpExceptions(INTERNAL_SERVER_ERROR);
	
	checkFileExistUpload(path);
	checkFolderExistUpload(path.substr(0, path.find_last_of('/')));

	body->moveBodyFile(path);
	resp->addHeader("Location", Uri::getPathInfo(req->getLoc(), req->getUri()));
	
	throw HttpExceptions(CREATED);
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
	
	if (stat(sock.getReq().getPathTranslated().c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(NOT_FOUND);
		}
	}

	if (S_ISDIR(infos.st_mode))
	{
		sock.getReq().setRedirect(sock.getReq().getUri() + "/");
		sock.getResp().addHeader("Location", sock.getReq().getUri() + "/");
		sock.getResp().setStatusCode(MOVED_PERMANENTLY);
		sock.getResp().setRespType(HttpResponse::REDIRECT);
		return (true);
	}
	
	if (!S_ISREG(infos.st_mode))
		throw HttpExceptions(NOT_FOUND);

	if (access(sock.getReq().getPathTranslated().c_str(), R_OK) == -1)
		throw HttpExceptions(FORBIDDEN);
	
	sock.getReq().setFilePath(sock.getReq().getPathTranslated());
	sock.getReq().setFileSize(infos.st_size);
	sock.getResp().setStatusCode(OK);
	sock.getResp().addHeader("Content-Length", infos.st_size);
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
	sock.getResp().addHeader("Location", redirectDirective->getValue() + "/");
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
	LOG_DEB(str);
	struct stat infos;
	std::string indexPath = Uri::buildUri(
			sock.getReq().getPathTranslated(), str);

	LOG_DEB(indexPath);

	if (stat(indexPath.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			default:
				return (false);
		}
	}

	if (!S_ISREG(infos.st_mode))
		return (false);

	if (access(indexPath.c_str(), R_OK) == -1)
		throw HttpExceptions(FORBIDDEN);
	
	sock.getReq().setFilePath(indexPath);
	sock.getReq().setFileSize(infos.st_size);
	sock.getResp().setStatusCode(OK);
	sock.getResp().addHeader("Content-Length", infos.st_size);
	sock.getResp().setRespType(HttpResponse::STATIC_FILE);
	return (true);
}

bool RequestHandling::isDirctoryListing(Socket &sock)
{
	if (sock.getReq().getUri().size() && *sock.getReq().getUri().rbegin() != '/')
		return (false);
	
	sock.getReq().setPathTranslated(
		Uri::trimSlashEnd(sock.getReq().getPathTranslated()));
	struct stat infos;
	if (stat(sock.getReq().getPathTranslated().c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(NOT_FOUND);
		}
	}

	if (!S_ISDIR(infos.st_mode))
		throw HttpExceptions(NOT_FOUND);

	const Directive* directive = 
		sock.getReq().getLoc()->findDirective("autoindex");

	if (!directive || directive->getValue() != "on" || 
		access(sock.getReq().getPathTranslated().c_str(), R_OK) == -1)
		throw HttpExceptions(FORBIDDEN);
	
	sock.getResp().setStatusCode(OK);
	sock.getResp().setRespType(HttpResponse::DIRECTORY_LISTING);
	return (true);
}

void RequestHandling::handleGet(Socket& sock)
{
	if (isRedirect(sock))
		return ;
			
	if (isCGI(sock))
		return ;
		
	if (isIndexFile(sock))
		return ;
			
	if (isDirctoryListing(sock))
		return ;
				
	if (isStaticFile(sock))
		return ;
		
	throw HttpExceptions(INTERNAL_SERVER_ERROR);
}

void RequestHandling::handlePost(Socket& sock)
{
	if (sock.getReq().getUri().size() && *sock.getReq().getUri().rbegin() == '/')
		throw HttpExceptions(METHOD_NOT_ALLOWED);

	LOG_DEB(sock.getReq().getUri());
	std::string	path = sock.getReq().getPathTranslated();

	handleBodyLength(sock);
	checkFileExistUpload(path);
	checkFolderExistUpload(path.substr(0, path.find_last_of('/')));
	sock.getReq().setState(HttpParser::HTTP_BODY);
}

void RequestHandling::handleBodyLength(Socket& sock)
{
	bool te = sock.getReq().findHeader("TRANSFER-ENCODING");
	bool cl = sock.getReq().findHeader("CONTENT-LENGTH");
	
	if (te && cl)
		throw HttpExceptions(BAD_REQUEST);
	
	if (te)
		handleTE(sock);
	else if (cl)
		handleContentLength(sock);
	else
		throw HttpExceptions(LENGTH_REQUIRED);
}

void RequestHandling::handleTE(Socket& sock)
{
	std::string value = sock.getReq().findHeaderValue("TRANSFER-ENCODING");
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (value != "chunked")
		throw HttpExceptions(NOT_IMPLEMENTED);
	
	sock.getReq().setTE(true);
}

void RequestHandling::handleContentLength(Socket& sock)
{
	std::string value = sock.getReq().findHeaderValue("CONTENT-LENGTH");

	if (value.empty() || 
		value.find_first_not_of("0123456789") != std::string::npos)
		throw HttpExceptions(BAD_REQUEST);

	std::istringstream iss(value);
	size_t cl;
    iss >> cl;

	if (iss.fail())
		throw HttpExceptions(BAD_REQUEST);
	
	sock.getReq().setContentLength(cl);
}

void RequestHandling::checkFileExistUpload(const std::string& path)
{
	struct stat infos;

	if (stat(path.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case ENOENT:
				return ;
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOTDIR:
			default:
				throw HttpExceptions(NOT_FOUND);
		}
	}
	throw HttpExceptions(CONFLICT);
}

void RequestHandling::checkFolderExistUpload(const std::string& dir)
{
	struct stat infos;

	if (stat(dir.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(NOT_FOUND);
		}
	}
}

void RequestHandling::handleDelete(Socket& sock)
{
	HttpRequest* req = &sock.getReq();
	std::string	path = sock.getReq().getPathTranslated();

	if (req->getUri().size() && *req->getUri().rbegin() == '/')
		throw HttpExceptions(METHOD_NOT_ALLOWED);
	
	LOG_DEB(req->getUri());

	checkFileExistDelete(path);

	if (std::remove(path.c_str()) != 0) 
	{
		switch (errno) 
		{
            case EACCES:
            case EPERM:
                throw HttpExceptions(FORBIDDEN);
            default:
                throw HttpExceptions(INTERNAL_SERVER_ERROR);
        }
	}
	throw HttpExceptions(NO_CONTENT);
}

void RequestHandling::checkFileExistDelete(const std::string& path)
{
	struct stat infos;

	if (stat(path.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(NOT_FOUND);
		}
	}
	if (!S_ISREG(infos.st_mode))
        throw HttpExceptions(METHOD_NOT_ALLOWED);
}

std::map<std::string, RequestHandling::HandlerFunc> 
	RequestHandling::initHandlers()
{
	std::map<std::string, RequestHandling::HandlerFunc> handlers;

	handlers["GET"] = &RequestHandling::handleGet;
	handlers["POST"] = &RequestHandling::handlePost;
	handlers["DELETE"] = &RequestHandling::handleDelete;

	return (handlers);
}