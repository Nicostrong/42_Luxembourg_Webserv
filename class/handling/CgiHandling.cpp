/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandling.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:11:56 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/06 10:05:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/handling/CgiHandling.hpp"

bool isStatusHeaderValid(const std::string& status)
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

bool isLocationValid(const std::string& loc)
{
    if (std::find_if(loc.begin(), loc.end(), std::not1(std::ptr_fun(isprint)))  
        != loc.end())
        return (false);
    
    
}

//https://datatracker.ietf.org/doc/html/rfc3875#section-1.4
/* Tocheck: Content-Type
            Location
*/