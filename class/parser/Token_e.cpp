/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_e.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:14:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:48:20 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for token error with info
 */
Token::TokenError::TokenError( const std::string &info ) throw()
{
	this->_msg = RED"[ERROR TOKEN] " + info + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
Token::TokenError::~TokenError( void ) throw()
{
	return ;
}

/*
 *	Error token with specific message
 */
const char*		Token::TokenError::what() const throw()
{
	return (this->_msg.c_str());
}
