/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:27:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 10:36:33 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Directive.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Directive::Directive( std::string &key, std::string &value ) 
	: _key(key), _value(value)
{
	return ;
}

/*
 *	Default destructor
 */
Directive::~Directive( void ) { return ; }

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
const std::string&		Directive::getKey( void ) const
{
	if (this->_key.empty())
		throw FieldsEmpty();
	return (this->_key);
}

/*
 *	get _value value
 */
const std::string&		Directive::getValue( void ) const
{
	if (this->_value.empty())
		throw FieldsEmpty();
	return (this->_value);
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
	out	<< BLUE << "------------- DIRECTIVE BLOCK -------------" << std::endl
		<< "name: " << src_object.getKey()
		<< " => [" << src_object.getValue() << "]" << std::endl
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