/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpExceptions.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:58:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:03:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/http/HttpExceptions.hpp"

HttpExceptions::HttpExceptions(size_t code) : _code(code) {}

HttpExceptions::HttpExceptions(const HttpExceptions& obj)
{
    this->_code = obj._code;
}

HttpExceptions::~HttpExceptions() throw () {}

HttpExceptions& HttpExceptions::operator=(const HttpExceptions& obj)
{
    if (this != &obj)
    {
        this->_code = obj._code;
    }
    return (*this);
}

size_t HttpExceptions::getCode() const
{
    return (this->_code);
}

const char* HttpExceptions::what() const throw()
{
	return ("Http Exception");
}