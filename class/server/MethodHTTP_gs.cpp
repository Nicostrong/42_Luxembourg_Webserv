/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP_gs.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:48:39 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:51:04 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/MethodHTTP.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	Return the string of allowed methods
 */
const std::string		MethodHTTP::getAllowed( void ) const
{
	std::string								ret;
	std::set<std::string>::const_iterator	it;

	for ( it = this->_allowed.begin(); it != this->_allowed.end(); ++it)
	{
		if (!ret.empty())
			ret += ", ";
		ret += *it;
	}
	return (ret);
}

/*******************************************************************************
 *							PRIVATE SETTER									   *
 ******************************************************************************/

/*
 *	Allow all method
 */
void	MethodHTTP::allowAll( void )
{
	this->_allowed.insert(MethodHTTP::_validMethods.begin(), MethodHTTP::_validMethods.end());
	return ;
}

/*
 *	Add a method on the array allowed methods
 */
void	MethodHTTP::allow( const std::string &method )
{
	if (!isMethod(method))
		throw MethodUnknow(method);
	this->_allowed.insert(method);
	return ;
}