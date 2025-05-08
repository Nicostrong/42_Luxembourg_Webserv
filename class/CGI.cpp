/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/08 09:36:24 by fdehan           ###   ########.fr       */
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
    
}

std::vector<std::string> getCGIEnv(const HttpRequest& req, const Server& serv)
{
    std::vector<std::string> env;

    env.push_back(getRawEnv("SERVER_SOFTWARE", SERVER_SOFT));
    env.push_back(getRawEnv("GATEWAY_INTERFACE", CGI_REVISION));
    env.push_back(getRawEnv("SERVER_PROTOCOL", req.getHTTP()));
    env.push_back(getRawEnv("SERVER_PORT", serv.getPort()));
    env.push_back(getRawEnv("REQUEST_METHOD", req.getMethod()));
    env.push_back(getRawEnv("PATH_INFO", req.getMethod()));

    std::map<std::string, std::string>::const_iterator it;
    
    for (it = req.getHeaders().begin(); it != req.getHeaders().end(); it++)
        env.push_back(getRawEnv("HTTP_" + it->first, it->second));
}

template <typename T>
std::string getRawEnv(const std::string& key, const T& value)
{
    std::ostringstream oss;

    oss << key << "=" << value;
    return (oss.str());
}
