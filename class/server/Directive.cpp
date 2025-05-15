/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:27:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 14:10:13 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Directive.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Directive::Directive( Token*& directiveTokens )
{
	std::string					key = directiveTokens->getValue();
	std::list<std::string>		lValue;

	while (directiveTokens && directiveTokens->getType() != Token::SEMICOLON)
	{
		if (directiveTokens->getType() == Token::DIR_V)
			lValue.push_back(directiveTokens->getValue());
		directiveTokens = directiveTokens->getNext();
	}
	if (!key.empty() || lValue.empty())
		throw FieldsEmpty();
	this->_key = key;
	this->_lValue = lValue;
	return ;
}

/*
 *	Default destructor
 */
Directive::~Directive( void )
{
	return ;
}

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

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error fields empty
 */
const char		*Directive::FieldsEmpty::what() const throw()
{
	return  (RED "[ERROR] Fields of Directive object empty !" RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, const Directive &src_object )
{
	const std::list<std::string>&				values = src_object.getValues();
	std::list<std::string>::const_iterator		it;
	bool										first = true;

	out	<< BLUE << "------------- DIRECTIVE BLOCK -------------" << std::endl
		<< "name: " << src_object.getKey()
		<< " => [";
	
	for (it = values.begin(); it != values.end(); ++it)
	{
		if (!first)
			out << ", ";
		out << *it;
		first = false;
	}
	out << "]" << std::endl
		<< "------------------------------------------"	<< RESET << std::endl;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef DIR

#include "../includes/Directive.hpp"
 
int	main( void )
{
	std::string	key = "toto";
	std::string	value = "le meilleur amis de l homme!!";
	Directive*	dir = new Directive(key, value);

	std::cout << obj << std::endl;
	delete dir;
	return (0);
}

#endif