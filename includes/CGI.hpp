/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:44 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/14 14:17:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "lib.hpp"
#include "HttpRequest.hpp"
#include "EventMonitoring.hpp"
#include "Server.hpp"
#include "IEventHandler.hpp"

class CGI : public IEventHandler
{
    public:
        CGI(EventMonitoring& em, const HttpRequest& req, HttpResponse& resp, 
			const Server& ctx, const std::string& remoteIp);
        CGI(const CGI& obj);
        ~CGI();
        CGI&    operator=(const CGI& obj);
        void	initCGI();
        
    private:
        const std::vector<std::string> getEnv() const;
        
        template <typename T>
        std::string  getRawEnv(const std::string& key, 
            const T& value) const;
        
        const std::vector<const char*> getCArray(const std::vector<std::string>& in) 
            const;
            
        EventMonitoring&    _em;
        const HttpRequest&  _req;
        HttpResponse&       _resp;
        const Server&       _ctx;
        std::string         _remoteIp;
};

#endif