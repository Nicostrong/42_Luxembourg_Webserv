/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:01 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/21 09:27:05 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CGI.hpp"

CGI::CGI(/*Socket& sock*/) : /*_sock(sock),*/ _pid(0)
{}

CGI::~CGI() {}


void	init()
{
	//const std::vector<std::string> env;

	//execve("", env.data(), env);
}

void CGI::launch()
{
    this->_pid = fork();
    if (this->_pid < 0)
    {
        LOG_DEB("Fork failed");
    }
    if (this->_pid == 0)
    {
        try {
            {
                std::vector<char *> vect(1);
                if (execve("", vect.data(), vect.data()) == -1)
                    throw std::runtime_error("execve failed");
            }
        } catch (...) {
            return ;
        }
    }
    else
    {
        this->_in.closeOut();
        this->_out.closeIn();
    }
}

/*const std::vector<std::string> CGI::getEnv() const
{
    std::vector<std::string> env;

    // Server specific

    env.push_back(getRawEnv("SERVER_SOFTWARE", SERVER_VER).c_str());
    env.push_back(getRawEnv("SERVER_NAME", "")); //SHoudl implement correctly
    env.push_back(getRawEnv("GATEWAY_INTERFACE", CGI_REVISION));

    // Request specific

    env.push_back(getRawEnv("SERVER_PROTOCOL", this->_req.getHTTP()));
    env.push_back(getRawEnv("SERVER_PORT", this->_ctx.getPort()8000));
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

const std::vector<const char*> CGI::getCArray(const std::vector<std::string>& in) 
	const
{
	std::vector<const char*> out;
	std::vector<std::string>::const_iterator it;
	
	for (it = in.begin(); it != in.end(); ++it)
		out.push_back(it->c_str());
	return (out);
}

template <typename T>
std::string CGI::getRawEnv(const std::string& key, const T& value) const
{
    std::ostringstream oss;

    oss << key << "=" << value;
    return (oss.str());
}*/
