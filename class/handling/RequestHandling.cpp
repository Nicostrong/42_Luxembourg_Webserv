/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:27:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 11:34:15 by fdehan           ###   ########.fr       */
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
		entryAddr.getIp(), entryAddr.getPort(), req->findHeaderValue("Host"));

	sock.getHandler().getHttpParser().setState(HttpParser::HTTP_HANDLED);

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
	sock.getHandler().getHttpParser().setState(HttpParser::HTTP_HANDLED);
	
	HttpRequest* req = &sock.getReq();
	Body* body = req->getBody();
	HttpResponse* resp = &sock.getResp();
	std::string	path = req->getPathTranslated();

	if (resp->getRespType() == HttpResponse::REDIRECT)
		return ;
	
	if (resp->getRespType() == HttpResponse::CGI)
	{
		sock.getHandler().setCGI(sock);
		sock.getHandler().getCGI()->execCGI();
		return ;
	}

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

/*
 *	CHECK CORRECTLY THE EXTENSION
 */
bool RequestHandling::isCGI(Socket& sock)
{
	std::string								ext = sock.getReq().getExtension();
	const Location*							loc = sock.getReq().getLoc();
	std::list<std::string>					extensions = loc->getAllCGIExtension();
	std::list<std::string>::const_iterator	it;

	for (it = extensions.begin(); it != extensions.end(); ++it)
		if (ext == *it)
			return (true);
	return (false);
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
	sock.getResp().addHeader("Location", redirectDirective->getUriReturn());
	LOG_DEB(redirectDirective->getCodeReturn());
	sock.getResp().setStatusCode((HttpBase::HttpCode)redirectDirective->getCodeReturn());
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
		if (!checkCGIext(sock))
		{
			LOG_DEB("FILE NOT FOUND");
			throw HttpExceptions(HttpBase::NOT_FOUND);
		}
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
	HttpRequest* req = &sock.getReq();
	std::string	path = req->getPathTranslated();
	
	if (isRedirect(sock))
	{
		handleBodyLength(sock);
		sock.getHandler().setBodyRequired(sock);
		if (!req->isTE() && req->getContentLength() < 1)
			handleBody(sock);
		return ;
	}
	
	if (req->getUri().size() && *req->getUri().rbegin() == '/')
		throw HttpSevereExceptions(HttpBase::METHOD_NOT_ALLOWED);
	
	if (isCGI(sock))
	{
		handleBodyLength(sock);
		LOG_DEB("IsCGI dans POST");
		sock.getResp().setRespType(HttpResponse::CGI);
		setAttributes(sock);
		
		if (!checkCGIext(sock))
			throw HttpSevereExceptions(HttpBase::NOT_FOUND);
		
		sock.getHandler().setBodyRequired(sock);
		LOG_DEB(req->getContentLength());
		if (!req->isTE() && req->getContentLength() < 1)
			handleBody(sock);
		return ;
	}

	if (req->findHeader("Content-Type"))
	{
		std::string value = req->findHeaderValue("Content-Type");
		std::string mimetype = value.substr(0, value.find(';'));

		mimetype = HttpBase::normalizeHeaderValue(mimetype);
		
		if (mimetype != "text/plain")
			throw HttpSevereExceptions(HttpBase::UNSUPPORTED_MEDIA_TYPE);
	}

	checkFileExistUpload(path);
	checkFolderExistUpload(path.substr(0, path.find_last_of('/')));
	sock.getHandler().setBodyRequired(sock);
	if (!req->isTE() && req->getContentLength() < 1)
		handleBody(sock);
}

void RequestHandling::handleBodyLength(Socket& sock)
{
	bool te = sock.getReq().findHeader("Transfer-Encoding");
	bool cl = sock.getReq().findHeader("Content-Length");
	
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
	std::string value = sock.getReq().findHeaderValue("Transfer-Encoding");
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (value != "chunked")
		throw HttpSevereExceptions(HttpBase::NOT_IMPLEMENTED);
	
	sock.getReq().setTE(true);
}

void RequestHandling::handleContentLength(Socket& sock)
{
	std::string value = sock.getReq().findHeaderValue("Content-Length");

	if (value.empty() || 
		value.find_first_not_of("0123456789") != std::string::npos)
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	std::istringstream iss(value);
	size_t cl;
    iss >> cl;

	if (iss.fail())
		throw HttpSevereExceptions(HttpBase::BAD_REQUEST);

	if (sock.getReq().getServer()->getMaxSizeBody() && cl > sock.getReq().getServer()->getMaxSizeBody())
		throw HttpSevereExceptions(HttpBase::CONTENT_TOO_LARGE);
	
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

	if (isRedirect(sock))
		return ;

	if (isCGI(sock))
	{
		LOG_DEB("IsCGI dans DELETE");
		sock.getResp().setRespType(HttpResponse::CGI);
		setAttributes(sock);

		if (!checkCGIext(sock))
			throw HttpExceptions(HttpBase::NOT_FOUND);
		
		sock.getHandler().setCGI(sock);
		sock.getHandler().getCGI()->execCGI();
		return ;
	}
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
	HttpRequest*			req = &socket.getReq();
	const Location*			loc = req->getLoc();
	const std::string&		pathTranslated = req->getPathTranslated();

	req->setCgiScript(pathTranslated.substr(pathTranslated.find_last_of('/') + 1));
	//req->setCgiPath(loc->getCGIPathUri(pathTranslated));
	req->setCgiPath(loc->getCGIPathUri(req->getExtension()));
	req->setPathInfo(loc->getPath());
	req->setFilePath(pathTranslated);
	req->setRedirect(loc->getDirectiveValue("return"));
	return ;
}

bool	RequestHandling::checkCGIext( Socket& sock )
{
	struct stat		buffer;
	std::string		path = sock.getReq().getPathTranslated();

	LOG_DEB("CHECK CGI: " << path);
	
	return (stat(path.c_str(), &buffer) == 0);
}