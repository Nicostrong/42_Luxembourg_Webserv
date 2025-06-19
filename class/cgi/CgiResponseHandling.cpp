/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseHandling.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:27:09 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 15:04:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cgi/CgiResponseHandling.hpp"

void CgiResponseHandling::handleHeaders(Socket& sock)
{
	// Should handle cgi response
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