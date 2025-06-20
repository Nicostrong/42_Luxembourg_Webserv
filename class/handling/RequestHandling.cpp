/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 16:55:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/handling/RequestHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

std::map<std::string, RequestHandling::HandlerFunc> RequestHandling::_handlers =
	RequestHandling::initHandlers();

void RequestHandling::handleHeaders(Socket& sock)
{
	const Endpoint entryAddr = sock.getEntryAddr();
	HttpRequest* req = &sock.getReq();
	HttpResponse* resp = &sock.getResp();
	const Server*	ctx = sock.getSM().getMatchingServer(
		entryAddr.getIp(), entryAddr.getPort(), req->findHeaderValue("HOST"));

	LOG_DEB(req->getUri());

	if (!ctx)
		throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);

	req->setServer(*ctx);
	resp->addHeader("Content-Length", 0);
	resp->addHeader("Connection", "keep-alive");

	if (std::strcmp(req->getHttpVersion().c_str(), SUPPORTED_HTTPVER) != 0)
		throw HttpSevereExceptions(HttpBase::HTTP_VERSION_NOT_SUPPORTED);
	
	if (!MethodHTTP::isMethodImplemented(req->getMethod()))
		throw HttpExceptions(HttpBase::NOT_IMPLEMENTED);

	req->setLoc(
		ctx->getMatchingLoc(req->getUri()));

	if (!req->getLoc())
		throw HttpExceptions(HttpBase::NOT_FOUND);

	if (!req->getLoc()->getMethod()->isAllowed(req->getMethod()))
		throw HttpExceptions(HttpBase::METHOD_NOT_ALLOWED);

	req->setPathTranslated(
			Uri::buildRealAbsolute(*ctx, req->getLoc(), req->getUri()));
	
	_handlers[req->getMethod()](sock);
}

void RequestHandling::handleBody(Socket& sock)
{
	//SHould handle everything else than upload
	HttpRequest* req = &sock.getReq();
	Body* body = req->getBody();
	HttpResponse* resp = &sock.getResp();
	std::string	path = req->getPathTranslated();
	
	if (!body)
		throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
	
	checkFileExistUpload(path);
	checkFolderExistUpload(path.substr(0, path.find_last_of('/')));

	body->moveBodyFile(path);
	resp->addHeader("Location", Uri::getPathInfo(req->getLoc(), req->getUri()));
	
	throw HttpExceptions(HttpBase::CREATED);
}

bool	RequestHandling::ends_with( const std::string& str, const std::string& suffix )
{
	if (str.length() >= suffix.length())
		return (str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0);
	return (false);
}

bool RequestHandling::isCGI(Socket& sock)
{
	std::string		uri = sock.getReq().getUri();
	size_t			queryPos = uri.find('?');

	if (queryPos != std::string::npos)
    	uri = uri.substr(0, queryPos);
	LOG_DEB(uri);

	return (RequestHandling::ends_with(uri, ".py") || RequestHandling::ends_with(uri, ".php"));
}
/*
	// CGI METHODOLOGY NOT CORRECT
	
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
*/

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
				throw HttpExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(HttpBase::NOT_FOUND);
		}
	}

	if (S_ISDIR(infos.st_mode))
	{
		sock.getReq().setRedirect(sock.getReq().getUri() + "/");
		sock.getResp().addHeader("Location", sock.getReq().getUri() + "/");
		sock.getResp().setStatusCode(HttpBase::MOVED_PERMANENTLY);
		sock.getResp().setRespType(HttpResponse::REDIRECT);
		return (true);
	}
	
	if (!S_ISREG(infos.st_mode))
		throw HttpExceptions(HttpBase::NOT_FOUND);

	if (access(sock.getReq().getPathTranslated().c_str(), R_OK) == -1)
		throw HttpExceptions(HttpBase::FORBIDDEN);
	
	sock.getReq().setFilePath(sock.getReq().getPathTranslated());
	sock.getReq().setFileSize(infos.st_size);
	sock.getResp().setStatusCode(HttpBase::OK);
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
	sock.getResp().setStatusCode(HttpBase::FOUND);
	sock.getResp().setRespType(HttpResponse::REDIRECT);
	return (true);
}

bool RequestHandling::isIndexFile(Socket& sock)
{
	HttpRequest* req = &sock.getReq();
	HttpResponse* resp = &sock.getResp();
	const Server* serv = req->getServer();
	struct stat infos;
	
	if (req->getUri().size() && *req->getUri().rbegin() != '/')
		return (false);
	
	std::string str = serv->getLocIndex(
		req->getLoc());
	std::string indexPath = Uri::buildUri(
			req->getPathTranslated(), str);

	if (stat(indexPath.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			default:
				return (false);
		}
	}

	if (!S_ISREG(infos.st_mode))
		return (false);

	if (access(indexPath.c_str(), R_OK) == -1)
		throw HttpExceptions(HttpBase::FORBIDDEN);
	
	req->setFilePath(indexPath);
	req->setFileSize(infos.st_size);
	resp->setStatusCode(HttpBase::OK);
	resp->addHeader("Content-Length", infos.st_size);
	resp->setRespType(HttpResponse::STATIC_FILE);
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
				throw HttpExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(HttpBase::NOT_FOUND);
		}
	}

	if (!S_ISDIR(infos.st_mode))
		throw HttpExceptions(HttpBase::NOT_FOUND);

	const Directive* directive = 
		sock.getReq().getLoc()->findDirective("autoindex");

	if (!directive || directive->getValue() != "on" || 
		access(sock.getReq().getPathTranslated().c_str(), R_OK) == -1)
		throw HttpExceptions(HttpBase::FORBIDDEN);
	
	sock.getResp().setStatusCode(HttpBase::OK);
	sock.getResp().setRespType(HttpResponse::DIRECTORY_LISTING);
	return (true);
}

// this goes somewhere before CGI and gets us the string to pass to CGI
std::string RequestHandling::getQueryString(const std::string& request)
{
	std::string		data;
	std::string		tmp = request;

    if (tmp.find("?") != std::string::npos)
    {
        tmp = tmp.substr(tmp.find("?") + 1);
        data = tmp.substr(0, tmp.find_first_of(" \t"));
    }
	return (data);
}

void RequestHandling::handleGet(Socket& sock)
{

	if (isRedirect(sock))
		return ;
			
	if (isCGI(sock))
	{
		LOG_DEB("IsCGI dans GET");
		sock.getResp().setRespType(HttpResponse::CGI);
		setAttributes(sock);
		sock.getHandler().setCGI(sock);
		sock.getHandler().getCGI()->execCGI();
		return ;
	}
	
	if (isIndexFile(sock))
		return ;
			
	if (isDirctoryListing(sock))
		return ;
				
	if (isStaticFile(sock))
		return ;
		
	throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
}

void RequestHandling::handlePost(Socket& sock)
{
	if (sock.getReq().getUri().size() && *sock.getReq().getUri().rbegin() == '/')
		throw HttpSevereExceptions(HttpBase::METHOD_NOT_ALLOWED);

	LOG_DEB(sock.getReq().getUri());
	std::string	path = sock.getReq().getPathTranslated();
	if (isCGI(sock))
	{
		LOG_DEB("IsCGI dans POST");
		sock.getResp().setRespType(HttpResponse::CGI);
		setAttributes(sock);
		sock.getHandler().setCGI(sock);
		sock.getHandler().getCGI()->execCGI();
		return ;
	}
	handleBodyLength(sock);
	checkFileExistUpload(path);
	checkFolderExistUpload(path.substr(0, path.find_last_of('/')));
	sock.getHandler().setBodyRequired();
}

void RequestHandling::handleBodyLength(Socket& sock)
{
	bool te = sock.getReq().findHeader("TRANSFER-ENCODING");
	bool cl = sock.getReq().findHeader("CONTENT-LENGTH");
	
	if (te && cl)
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);
	
	if (te)
		handleTE(sock);
	else if (cl)
		handleContentLength(sock);
	else
		throw HttpSevereExceptions(HttpBase::LENGTH_REQUIRED);
}

void RequestHandling::handleTE(Socket& sock)
{
	std::string value = sock.getReq().findHeaderValue("TRANSFER-ENCODING");
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (value != "chunked")
		throw HttpExceptions(HttpBase::NOT_IMPLEMENTED);
	
	sock.getReq().setTE(true);
}

void RequestHandling::handleContentLength(Socket& sock)
{
	std::string value = sock.getReq().findHeaderValue("CONTENT-LENGTH");

	if (value.empty() || 
		value.find_first_not_of("0123456789") != std::string::npos)
		throw HttpExceptions(HttpBase::BAD_REQUEST);

	std::istringstream iss(value);
	size_t cl;
    iss >> cl;

	if (iss.fail())
		throw HttpExceptions(HttpBase::BAD_REQUEST);
	
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
				throw HttpSevereExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpSevereExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOTDIR:
			default:
				throw HttpSevereExceptions(HttpBase::NOT_FOUND);
		}
	}
	throw HttpSevereExceptions(HttpBase::CONFLICT);
}

void RequestHandling::checkFolderExistUpload(const std::string& dir)
{
	struct stat infos;

	if (stat(dir.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpSevereExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpSevereExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpSevereExceptions(HttpBase::NOT_FOUND);
		}
	}
}

void RequestHandling::handleDelete(Socket& sock)
{
	HttpRequest* req = &sock.getReq();
	std::string	path = sock.getReq().getPathTranslated();

	if (req->getUri().size() && *req->getUri().rbegin() == '/')
		throw HttpExceptions(HttpBase::METHOD_NOT_ALLOWED);
	
	LOG_DEB(req->getUri());

	checkFileExistDelete(path);

	if (std::remove(path.c_str()) != 0) 
	{
		switch (errno) 
		{
            case EACCES:
            case EPERM:
                throw HttpExceptions(HttpBase::FORBIDDEN);
            default:
                throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
        }
	}
	throw HttpExceptions(HttpBase::NO_CONTENT);
}

void RequestHandling::checkFileExistDelete(const std::string& path)
{
	struct stat infos;

	if (stat(path.c_str(), &infos) == -1)
	{
		switch (errno)
		{
			case EACCES:
				throw HttpExceptions(HttpBase::FORBIDDEN);
			case EIO:
			case ELOOP:
			case EOVERFLOW:
				throw HttpExceptions(HttpBase::INTERNAL_SERVER_ERROR);
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
			default:
				throw HttpExceptions(HttpBase::NOT_FOUND);
		}
	}
	if (!S_ISREG(infos.st_mode))
        throw HttpExceptions(HttpBase::METHOD_NOT_ALLOWED);
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

void	RequestHandling::setAttributes( Socket& socket )
{
	HttpRequest*		req = &socket.getReq();
	const Location*		loc = req->getLoc();
	size_t				pos = req->getUri().find_last_of('?');

	req->setCgiScript(req->getPathTranslated().substr(req->getPathTranslated().find_last_of('/') + 1));
	req->setCgiPath(loc->getCGIPathUri(req->getPathTranslated()));
	req->setPathInfo(loc->getPath());
	req->setFilePath(req->getPathTranslated());
	req->setRedirect(loc->getDirectiveValue("return"));
	if (pos != std::string::npos)
    	req->setQueryParams(req->getUri().substr(pos + 1));
	else
	    req->setQueryParams("");
	return ;
}
