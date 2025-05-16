/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 14:32:03 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGIDirective.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
CGIDirective::CGIDirective( Token*& tokens) 
{
	if (tokens->getType() != Token::CGI_K)
		throw BadTokenType();
	this->_extension = tokens->getValue();
	tokens = tokens->getNext();
	if (!tokens || tokens->getType() != Token::CGI_V)
		throw BadTokenType();
	this->_path = tokens->getValue();
	return ;
}

/*
 *	Default destructor
 */
CGIDirective::~CGIDirective( void )
{
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _extension value
 */
const std::string&		CGIDirective::getExtension( void ) const
{
	if (this->_extension.empty())
		throw FieldsEmpty();
	return (this->_extension);
}

/*
 *	get _path value
 */
const std::string&		CGIDirective::getPath( ) const
{
	if (this->_path.empty())
		throw FieldsEmpty();
	return (this->_path);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error fields empty
 */
const char*     CGIDirective::FieldsEmpty::what() const throw()
{
	return  (RED "[ERROR CGI] Fields of CGIDirective object empty !" RESET);
}

/*
 *	Bad token type
 */
const char*     CGIDirective::BadTokenType::what() const throw()
{
	return  (RED "[ERROR CGI] Bad token type for creating CGIDirective !" RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream& out, const CGIDirective& src_object )
{
	out	<< BLUE << "------------- CGIDIRECTIVE BLOCK -------------" << std::endl
		<< "name:\n\t" << src_object.getExtension()
		<< " => [" << src_object.getPath() << "]" << std::endl
		<< "------------------------------------------"	<< RESET << std::endl;
	return (out);
}