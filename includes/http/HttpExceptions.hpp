/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpExceptions.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:59:20 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:31:20 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPEXCEPTIONS_HPP
# define HTTPEXCEPTIONS_HPP

# include "./../lib.hpp"

class   HttpExceptions : public std::exception
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