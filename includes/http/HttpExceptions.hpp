/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpExceptions.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:59:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:04:49 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPEXCEPTIONS_HPP
# define HTTPEXCEPTIONS_HPP

#include "./../lib.hpp"

class HttpExceptions : public std::exception
{
    public:
        HttpExceptions(size_t code);
        HttpExceptions(const HttpExceptions& obj);
        virtual ~HttpExceptions() throw ();
        HttpExceptions&			operator=(const HttpExceptions& obj);
        virtual const char*		what() const throw();
        size_t					getCode() const;
    private:
        size_t					_code;
       
};

# endif