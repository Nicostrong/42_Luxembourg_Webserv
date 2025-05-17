/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_gs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:22 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:49:49 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Directive.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _key value
 */
const std::string&					Directive::getKey( void ) const
{
	if (this->_key.empty())
		throw FieldsEmpty();
	return (this->_key);
}

/*
 *	get the first value of _lValue
 */
const std::string&					Directive::getValue( void ) const
{
	if (this->_lValue.empty())
		throw FieldsEmpty();
	return (*this->_lValue.begin());
}
/*
 *	get _value value
 */
const std::list<std::string>&		Directive::getValues( void ) const
{
	if (this->_lValue.empty())
		throw FieldsEmpty();
	return (this->_lValue);
}