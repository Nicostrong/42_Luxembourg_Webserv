/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:30:05 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/20 15:02:23 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Uri.hpp"
#include "../includes/server/Server.hpp"

Uri::Uri() {}

Uri::Uri(const Uri& obj) 
{
    (void)obj;
}

Uri::~Uri() {}

Uri& Uri::operator=(const Uri& obj)
{
    (void)obj;
    return (*this);
}

std::string Uri::trimSlashBegin(const std::string& uri)
{
    if (uri.size() > 0 && *uri.begin() == '/')
        return (uri.substr(1));
    return (uri);
}

std::string Uri::trimSlashEnd(const std::string& uri)
{
    if (uri.size() > 0 && *uri.rbegin() == '/')
        return (uri.substr(0, uri.size() - 1));
    return (uri);
}

std::string Uri::buildUri(std::string p1, std::string p2)
{
    p1 = trimSlashEnd(p1);
    p2 = trimSlashBegin(p1);
    return (p1 + '/' + p2);
}

std::string Uri::getPathInfo(const Location *loc, std::string uri)
{
    std::string locPath = loc->getPath();

    locPath = trimSlashEnd(locPath);
    uri = uri.substr(locPath.size());
    return (uri);
}

std::string Uri::buildByReplacingLoc(const Location* loc, std::string uri, 
    std::string replacement)
{
    std::string locPath = loc->getPath();

    locPath = trimSlashEnd(locPath);
    replacement = trimSlashEnd(replacement);

    uri = uri.replace(0, locPath.size(), replacement);
    return (uri);
}

std::string Uri::buildRealAbsolute(const Server& serv, const Location* loc, 
    std::string uri)
{
    const Directive* rootDirective = loc->findDirective("root");
	std::string location = loc->getPath();
	std::string	rootPath = serv.getPath();
	
	if (rootDirective)
		rootPath = rootDirective->getValue();
	location = trimSlashEnd(location);
	rootPath = trimSlashEnd(rootPath);
	
	uri = uri.replace(0, location.size(), rootPath);
	LOG_DEB("Path constructed: " + uri);
	return (uri);
}

std::string Uri::buildRealRelative(const Server& serv, const Location* loc, 
    std::string uri)
{
    const Directive* rootDirective = loc->findDirective("root");
	std::string	rootPath = serv.getPath();
	
	if (rootDirective)
		rootPath = rootDirective->getValue();
	rootPath = trimSlashEnd(rootPath);
	LOG_DEB("Path constructed from relative: " + uri);
	return (rootPath + uri);
}

std::string Uri::getCgiPath(const std::list<Directive*>& cgiDirectives, 
    const Location* loc, const std::string& uri)
{
    std::string token;
     
    if (uri.size() == 0)
        return ("");
    
    std::string location = trimSlashEnd(loc->getPath());
    std::string relativePath = uri.substr(location.size());
    
    if (relativePath == "/")
    {
        const Directive* index = loc->findDirective("index");
        if (index)
        {
            token = index->getValue();
            if (isCgiExtValid(cgiDirectives, token))
                return ('/' + token);
        }
    }
    else if (relativePath.size() > 1)
    {
        size_t slashPos = 0;
        std::string currFolder = "/";

        relativePath = trimSlashBegin(relativePath);
        while (relativePath.size() > 0 && slashPos != std::string::npos)
        {
            slashPos = relativePath.find('/');
            token = relativePath.substr(0, slashPos);

            if (isCgiExtValid(cgiDirectives, token))
                return (currFolder + token);
            
            if (slashPos != std::string::npos)
            {
                currFolder.append(token);
                currFolder.append("/");
                relativePath = relativePath.substr(slashPos + 1);
            }
        }
    }
    return ("");
}

bool Uri::isCgiExtValid(const std::list<Directive*>& cgiDirectives, 
        const std::string& filename)
{
    std::list<Directive*>::const_iterator it;
    std::string ext;

    for (it = cgiDirectives.begin(); it != cgiDirectives.end(); it++)
    {
        ext = (*it)->getValue();
        if (filename.size() >= ext.size() && 
                filename.substr(filename.size() - ext.size()) == ext)
            return (true);
    }
    return (false);
}
