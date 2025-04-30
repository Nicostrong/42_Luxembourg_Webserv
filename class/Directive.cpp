/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:27:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/30 13:50:26 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Directive.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/


Directive::Directive( void )
{
	return ;
}

/*
 *	Default constructor
 */
Directive::Directive( std::string &key, std::string &value )
	: _name(key)
{
	LOG_DEB("Directive constructor called");
	std::istringstream	stream(value);
	std::string			token;

	while (stream >> token)
		this->_values.push_back(token);
	if (this->_values.empty())
		throw DirectiveException();
	return ;
}

/*
 *	Default destructor
 */
Directive::~Directive( void )
{
	LOG_DEB("Directive destructor called");
	return ;
}

/*
 *	Copy constructor
 */
Directive::Directive( const Directive &src_object )
{
	*this = src_object;
	return ;
}

/*
 *	Copy assignment operator
 */
Directive		&Directive::operator=( const Directive &src_object )
{
	if (this != &src_object)
	{
		this->_name = src_object._name;
		this->_values = src_object._values;
	}
	return (*this);
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

 /*
  *	set the name attribut
  */
void			Directive::setName( std::string &name )
{
	this->_name = name;
	return ;
}

/*
 *	modifie the value at index x
 */
void			Directive::setValue( size_t index, std::string &value )
{
	if (index >= this->_values.size())
		throw DirectiveException();
	this->_values[index] = value;
	return ;
}

/*
 *	add a new value on the vector
 */
void			Directive::addValue( std::string &value )
{
	this->_values.push_back(value);
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
std::string		Directive::getName( void ) const
{
	return (this->_name);
}

/*
 *	get _value value
 */
std::string		Directive::getValue( int index ) const
{
	if (index < 0 || static_cast<size_t>(index) >= this->_values.size())
		throw DirectiveException();
	return (this->_values[index]);
}

/*
 *	get all _value value
 */
std::string		Directive::getAllValue( void ) const
{
	std::string	ret;

	for (size_t i = 0; i < this->_values.size(); i++)
	{
		ret += this->_values[i];
		if (i < this->_values.size() - 1)
			ret += ", ";
	}
	return (ret);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error creating server
 */
const char		*Directive::DirectiveException::what() const throw()
{
	return  (RED "[ERROR] Creating Directive !" RESET);
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
		<< "name: " << src_object.getName()
		<< " => [" << src_object.getAllValue() << "]" << std::endl
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
	Directive	obj;
	std::string	name;
	std::string	value_0;
	std::string	value_1;
	std::string	value_2;

	std::cout << obj << std::endl;

	name = "toto";
	value_0 = "un";
	value_1 = "deux";
	value_2 = "trois";
	obj.setName(name);
	obj.addValue(value_0);
	obj.addValue(value_1);
	obj.addValue(value_2);

	std::cout << obj << std::endl;
	
	return (0);
}

#endif