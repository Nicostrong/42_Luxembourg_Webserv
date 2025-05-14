/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 10:12:35 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CGI.hpp"

CGI::CGI(EventMonitoring& em, const HttpRequest& req, HttpResponse& resp, 
    const Server& ctx, const std::string& remoteIp) : _em(em), _req(req), _resp(resp), _ctx(ctx), _remoteIp(remoteIp) {}

CGI::CGI(const CGI& obj) : _em(obj._em), _req(obj._req), _resp(obj._resp), 
	_ctx(obj._ctx), _remoteIp(obj._remoteIp) {}

CGI::~CGI() {}

CGI& CGI::operator=(const CGI& obj) 
{
    if (this != &obj)
        this->_em = obj._em;
    return (*this);
}

void	initCGI()
{
	std::vector<std::string> env;
	//execve("", env.data(), env);
}

std::vector<const std::string> CGI::getEnv() const
{
    std::vector<const std::string> env;

    // Server specific

    env.push_back(getRawEnv("SERVER_SOFTWARE", SERVER_SOFT).c_str());
    env.push_back(getRawEnv("SERVER_NAME", "")); //SHoudl implement correctly
    env.push_back(getRawEnv("GATEWAY_INTERFACE", CGI_REVISION));

    // Request specific

    env.push_back(getRawEnv("SERVER_PROTOCOL", this->_req.getHTTP()));
    env.push_back(getRawEnv("SERVER_PORT", this->_ctx.getPort()));
    env.push_back(getRawEnv("REQUEST_METHOD", this->_req.getMethod()));
    env.push_back(getRawEnv("PATH_INFO", "")); //Should take it from handled
    env.push_back(getRawEnv("PATH_TRANSLATED", "")); //Should take it from handled
    env.push_back(getRawEnv("SCRIPT_NAME", "")); //Should take it from handled
    env.push_back(getRawEnv("QUERY_STRING", "")); //Should take it from handled
    env.push_back(getRawEnv("REMOTE_HOST", ""));
    env.push_back(getRawEnv("REMOTE_ADDR", this->_remoteIp));
    env.push_back(getRawEnv("AUTH_TYPE", ""));
    env.push_back(getRawEnv("REMOTE_USER", ""));
    env.push_back(getRawEnv("REMOTE_IDENT", ""));
    env.push_back(getRawEnv("CONTENT_TYPE", "")); //Should take it from header
    env.push_back(getRawEnv("CONTENT_LENGTH", "")); //Should take it from header

    // Request headers

    std::map<std::string, std::string>::const_iterator it;
    
    for (it = this->_req.getHeaders().begin(); 
			it != this->_req.getHeaders().end(); it++)
        env.push_back(getRawEnv("HTTP_" + it->first, it->second));
    return (env);
}

std::vector<const char*> CGI::getCArray(std::vector<const std::string>& in) 
	const
{
	std::vector<const char*> out;
	std::vector<const std::string>::const_iterator it;
	
	for (it = in.cbegin(); it != in.cend(); ++it)
		out.push_back(it->c_str());
	return (out);
}

template <typename T>
std::string CGI::getRawEnv(const std::string& key, const T& value) const
{
    std::ostringstream oss;

    oss << key << "=" << value;
    return (oss.str());
}
