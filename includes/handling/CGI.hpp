/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:46:44 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:39:06 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "./../lib.hpp"
# include "./../utils/Pipe.hpp"
# include "./../events/IEventHandler.hpp"
# include "./../events/EventMonitoring.hpp"
# include "./../server/Server.hpp"
# include "./../http/HttpRequest.hpp"
# include "./../networking/Socket.hpp"

class CGI : public IEventHandler
{
    public:
        class ForkClean : public std::exception {
			public:
				const char * what () const throw();
		};

        CGI(Socket& sock);
       
        ~CGI();
        

        void	init();
        void    launch(Socket& sock, const std::string& path);
        pid_t   getPid() const;
    private:
        CGI(const CGI& obj);
        CGI&    operator=(const CGI& obj);
        const std::vector<std::string> getEnv() const;
        
        template <typename T>
        std::string  getRawEnv(const std::string& key, 
            const T& value) const;
        
        const std::vector<const char*> getCArray(const std::vector<std::string>& in) 
            const;
        Socket& _sock;
        pid_t   _pid;
        Pipe    _in;
        Pipe    _out;
};

#endif