/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:27:09 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 09:04:17 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponseHandling.hpp"
#include "./../../includes/networking/Socket.hpp"

void CgiResponseHandling::handleHeaders(Socket& sock)
{
	//if (sock.get)
	(void)sock;
}

bool CgiResponseHandling::isStatusHeaderValid(const std::string& status)
{
	std::string codeStr;
	size_t pos = status.find(" ");

	codeStr = status.substr(0, pos);

	if (codeStr.size() != 3)
		return (false);

	if (codeStr.find_last_not_of("0123456789") != std::string::npos)
		return (false);

	int code = std::atoi(codeStr.c_str());

	return (code >= 100 && code < 600);
}

bool CgiResponseHandling::isLocationValid(const std::string& loc)
{
	/*if (std::find_if(loc.begin(), loc.end(), std::not1(std::ptr_fun(isprint)))  
		!= loc.end())
		return (false);*/
	(void)loc;
	return (true);
}

//https://datatracker.ietf.org/doc/html/rfc3875#section-1.4
/* Tocheck: Content-Type
			Location
*/