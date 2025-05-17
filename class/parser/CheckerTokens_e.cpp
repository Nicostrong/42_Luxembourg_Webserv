/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_e.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:12:46 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:46:52 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for checking tokens
 */
CheckerTokens::CheckerError::CheckerError( const std::string &data ) throw()
{
	this->_msg = RED"[ERROR CHECKERTOKENS] " + data + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
CheckerTokens::CheckerError::~CheckerError( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char		*CheckerTokens::CheckerError::what() const throw()
{
	return (this->_msg.c_str());
}