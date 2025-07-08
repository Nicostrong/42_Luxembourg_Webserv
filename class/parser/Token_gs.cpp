/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token_gs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:47:16 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 13:34:03 by nfordoxc         ###   Luxembourg.lu     */
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
		LOG_DEB("\t");
	LOG_DEB(RESET"Token [" << this->getTypeName() << "] - Value: " << this->_value);
	if (this->_next)
	{
		LOG_DEB(RESET"Next -> ");
		this->_next->printToken(true);
	}
	return ;
}

/*
 *	get the number of server on the config file
 */
int			Token::getNbServer( void )
{
	return (_nbServer);
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

/*
 *	Set the next token to NULL
 */
void			Token::setNextToNull( void )
{
	_next = NULL;
	return ;
}

/*
 *	increase the value of number of server
 */
void			Token::incServer( void )
{
	_nbServer++;
	return ;
}

/*
 *	init the value of static variable to 0
 */
void			Token::setNbServer( void )
{
	_nbServer = 0;
	return ;
}