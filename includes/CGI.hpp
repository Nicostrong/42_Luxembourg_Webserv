/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:44 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 08:28:02 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "lib.hpp"
#include "HttpRequest.hpp"
#include "EventMonitoring.hpp"
#include "Server.hpp"

class CGI
{
    public:
        CGI(EventMonitoring& em);
        CGI(const CGI& obj);
        ~CGI();
        CGI&    operator=(const CGI& obj);
        void    launchCGI(const HttpRequest& req, const Server& serv, 
            const std::string& remoteIp);
        static std::vector<std::string> getCGIEnv(const HttpRequest& req, const Server& serv, 
            const std::string& remoteIp);
        template <typename T>
        static std::string getRawEnv(const std::string& key, 
            const T& value);
        static bool isCgiValid(const std::string& cgiPath);
    private:
        EventMonitoring& _em;
};

#endif