/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_e.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:14:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 08:30:30 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Token.hpp"

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
