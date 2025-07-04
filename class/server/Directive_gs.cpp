/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_gs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:55:22 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/02 09:18:09 by fdehan           ###   ########.fr       */
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

/*
 *	get the code of return directive
 */
size_t		Directive::getCodeReturn( void ) const
{
	std::stringstream	ss(getValue());
	size_t				code;

	ss >> code;	
	return (code);
}

/*
 *	get the uri of return
 */
const std::string&		Directive::getUriReturn( void ) const
{
	const std::list<std::string>&		lValues = getValues();

	return (lValues.back());
}