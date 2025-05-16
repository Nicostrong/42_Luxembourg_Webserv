/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_gs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:22 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:55:41 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Directive.hpp"

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