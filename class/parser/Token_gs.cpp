/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_gs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:47:16 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:48:29 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Get the type of the token
 */
int				Token::getType( void ) const
{
	return (this->_type);
}

/*
 *	Get the value of the token
 */
std::string		Token::getValue( void ) const
{
	return (this->_value);
}

/*
 *	Get the name of the type of the token
 */
std::string		Token::getTypeName( void ) const
{
	static const char*	typeNames[] = {
			BLUE "SERVER" RESET,
			BLUE "SER_BLK_S" RESET,
			BLUE "SER_BLK_E" RESET,
			RED "ERROR_PAGE" RESET,
			RED "ERR_BLK_S" RESET,
			RED "ERR_BLK_E" RESET,
			YELLOW "LOCATION" RESET,
			YELLOW "LOC_BLK_S" RESET,
			YELLOW "LOC_BLK_E" RESET,
			GREEN "CGI" RESET,
			GREEN "CGI_BLK_S" RESET,
			GREEN "CGI_BLK_E" RESET,
			"CGI_K", "CGI_V", "HTTP_K", "HTTP_V",
			"DIR_K", "DIR_V", "SEMICOLON"
	};
	
	if (this->_type >= SERVER && this->_type <= SEMICOLON)
		return (typeNames[this->_type - SERVER]);
	return ("UNKNOWN_TYPE");
}

/*
 *	Get the next token
 */
Token*		Token::getNext( void ) const
{
	return (this->_next);
}

/*
 *	Print the token list
 */
void		Token::printToken( bool isNext ) const
{
	if (!isNext)
		std::cout << "\t";
	std::cout	<< "Token [" << getTypeName() << "] - Value: "
				<< this->_value << std::endl;
	if (this->_next)
	{
		std::cout << "Next -> ";
		this->_next->printToken(true);
	}
	return ;
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

/*
 *	Set the next token to NULL
 */
void			Token::setNextToNull( void )
{
	this->_next = NULL;
	return ;
}
