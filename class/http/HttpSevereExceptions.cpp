/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpSevereExceptions.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:34:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:04:09 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpSevereExceptions.hpp"

HttpSevereExceptions::HttpSevereExceptions(size_t code) : HttpExceptions(code) 
{}
        
HttpSevereExceptions::HttpSevereExceptions(const HttpSevereExceptions& obj) :
    HttpExceptions(obj) {}
        
HttpSevereExceptions::~HttpSevereExceptions() throw() {}

HttpSevereExceptions& 
    HttpSevereExceptions::operator=(const HttpSevereExceptions& obj)
{
    if (this != &obj)
        HttpExceptions::operator=(obj);
    return (*this);
}

const char* HttpSevereExceptions::what() const throw()
{
	return ("Http Severe Exception");
}