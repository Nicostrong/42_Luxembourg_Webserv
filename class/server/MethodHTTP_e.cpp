/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP_e.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:48:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:53:57 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MethodHTTP.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsong error with data
 */
MethodHTTP::MethodUnknow::MethodUnknow( const std::string &method ) throw()
{
	this->_msg = RED"[ERROR] Method unknow: " + method + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
MethodHTTP::MethodUnknow::~MethodUnknow( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char*		MethodHTTP::MethodUnknow::what() const throw()
{
	return (this->_msg.c_str());
}