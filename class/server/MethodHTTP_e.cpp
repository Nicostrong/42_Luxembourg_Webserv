/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP_e.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:48:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:50:59 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/MethodHTTP.hpp"

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