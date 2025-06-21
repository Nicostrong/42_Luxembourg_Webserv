/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:28:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/21 10:02:24 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSEHANDLING_HPP
# define CGIRESPONSEHANDLING_HPP

#include "./CgiResponse.hpp"
#include "./../http/HttpExceptions.hpp"

class Socket;

class CgiResponseHandling
{
    public:
        
		static void		handleHeaders(Socket& sock);
        static void 		handleStatusHeader(const std::string& status, Socket& sock);
		static void 		handleTE(Socket& sock);
		static void		handleContentLength(Socket& sock);
		
        static bool isLocationValid(const std::string& loc);
    private:
		CgiResponseHandling();
		CgiResponseHandling(const CgiResponseHandling& obj);
        ~CgiResponseHandling();
		CgiResponseHandling& operator=(const CgiResponseHandling& obj);

};

#endif