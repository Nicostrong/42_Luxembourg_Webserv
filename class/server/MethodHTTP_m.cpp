/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP_m.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:50:42 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/30 14:37:02 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/MethodHTTP.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	By default all method are allowed
 */
void	MethodHTTP::initDefault( void )
{
	this->_allowed.insert(MethodHTTP::_validMethods.begin(), MethodHTTP::_validMethods.end());
	return ;
}

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/

/*
 *	Check if the method is allowed
 */
bool	MethodHTTP::isAllowed( const std::string &method ) const
{
	return (this->_allowed.find(method) != this->_allowed.end());
}

/*
 *	Check if the method is a valid method
 */
bool	MethodHTTP::isMethod( const std::string &method )
{
	return (MethodHTTP::_validMethods.find(method) != MethodHTTP::_validMethods.end());
}

/*
 *	Check if the method is an implemented method
 */
bool	MethodHTTP::isMethodImplemented( const std::string &method )
{
	return (MethodHTTP::_implementedMethods.find(method) != MethodHTTP::_implementedMethods.end());
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, MethodHTTP const &src_object )
{
	out	<< MAGENTA << "------------- METHOD BLOCK -------------" << std::endl
		<< "Methods Allow:\n\t[" << src_object.getAllowed() << "]" << std::endl
		<< "------------------------------------------" <<RESET;
	return (out);
}