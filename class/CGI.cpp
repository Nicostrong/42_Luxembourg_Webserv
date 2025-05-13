/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/13 18:42:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CGI.hpp"

CGI::CGI(EventMonitoring& em) : _em(em) {}

CGI::CGI(const CGI& obj) : _em(obj._em) {}

CGI::~CGI() {}

CGI& CGI::operator=(const CGI& obj) 
{
    if (this != &obj)
        this->_em = obj._em;
    return (*this);
}

void    launchCGI(const HttpRequest& req, const Server& serv)
{
    (void)req;
    (void)serv;
}

std::vector<std::string> CGI::getCGIEnv(const HttpRequest& req, const Server& serv, 
    const std::string& remoteIp)
{
    std::vector<std::string> env;

    // Server specific

    env.push_back(getRawEnv("SERVER_SOFTWARE", SERVER_SOFT));
    env.push_back(getRawEnv("SERVER_NAME", "")); //SHoudl implement correctly
    env.push_back(getRawEnv("GATEWAY_INTERFACE", CGI_REVISION));

    // Request specific

    env.push_back(getRawEnv("SERVER_PROTOCOL", req.getHTTP()));
    env.push_back(getRawEnv("SERVER_PORT", serv.getPort()));
    env.push_back(getRawEnv("REQUEST_METHOD", req.getMethod()));
    env.push_back(getRawEnv("PATH_INFO", "")); //Should take it from handled
    env.push_back(getRawEnv("PATH_TRANSLATED", "")); //Should take it from handled
    env.push_back(getRawEnv("SCRIPT_NAME", "")); //Should take it from handled
    env.push_back(getRawEnv("QUERY_STRING", "")); //Should take it from handled
    env.push_back(getRawEnv("REMOTE_HOST", ""));
    env.push_back(getRawEnv("REMOTE_ADDR", remoteIp));
    env.push_back(getRawEnv("AUTH_TYPE", ""));
    env.push_back(getRawEnv("REMOTE_USER", ""));
    env.push_back(getRawEnv("REMOTE_IDENT", ""));
    env.push_back(getRawEnv("CONTENT_TYPE", "")); //Should take it from header
    env.push_back(getRawEnv("CONTENT_LENGTH", "")); //Should take it from header

    // Request headers

    std::map<std::string, std::string>::const_iterator it;
    
    for (it = req.getHeaders().begin(); it != req.getHeaders().end(); it++)
        env.push_back(getRawEnv("HTTP_" + it->first, it->second));
    return (env);
}

template <typename T>
std::string CGI::getRawEnv(const std::string& key, const T& value)
{
    std::ostringstream oss;

    oss << key << "=" << value;
    return (oss.str());
}

bool CGI::isCgiValid(const std::string& cgiPath)
{
    struct stat s;
    if (stat(cgiPath.c_str(), &s) == -1)
        return (false);
    //std::cout << s.st_mode &
    return (true);
}
