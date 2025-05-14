/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:39:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 14:53:32 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CGIDirective.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
CGIDirective::CGIDirective( std::string &extension, std::string &path ) 
	: _extension(extension), _path(path)
{
	return ;
}

/*
 *	Default destructor
 */
CGIDirective::~CGIDirective( void ) { return ; }

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
	return  (RED "[ERROR] Fields of CGIDirective object empty !" RESET);
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
		<< "name: " << src_object.getExtension()
		<< " => [" << src_object.getPath() << "]" << std::endl
		<< "------------------------------------------"	<< RESET << std::endl;
	return (out);
}