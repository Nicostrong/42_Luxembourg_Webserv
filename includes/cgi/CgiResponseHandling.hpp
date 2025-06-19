/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:28:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:39:48 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSEHANDLING_HPP
# define CGIRESPONSEHANDLING_HPP

#include "./CgiResponse.hpp"

class CgiResponseHandling
{
    public:
        
		void		handleHeaders(Socket& sock);
        static bool isStatusHeaderValid(const std::string& status);
        static bool isLocationValid(const std::string& loc);
    private:
		CgiResponseHandling();
		CgiResponseHandling(const CgiResponseHandling& obj);
        ~CgiResponseHandling();
		CgiResponseHandling& operator=(const CgiResponseHandling& obj);

};

#endif