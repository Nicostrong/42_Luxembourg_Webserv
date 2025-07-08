/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpSevereExceptions.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:35:12 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:33:30 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSEVEREEXCEPTIONS_HPP
# define HTTPSEVEREEXCEPTIONS_HPP

# include "./HttpExceptions.hpp"

class   HttpSevereExceptions : public   HttpExceptions
{
    public:

        HttpSevereExceptions(size_t code);
        HttpSevereExceptions(const HttpSevereExceptions& obj);
        virtual ~HttpSevereExceptions() throw ();
        HttpSevereExceptions&	operator=(const HttpSevereExceptions& obj);
        virtual const char*		what() const throw();

    private:
    
};

#endif