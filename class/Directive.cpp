/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:27:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 08:25:40 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Directive.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Directive::Directive( std::string &data )
{
	std::istringstream	stream(data);
	std::string			token;
	bool				first = true;

	while (stream >> token)
	{
		if (first)
		{
			this->_name = token;
			first = false;
		}
		else
			this->_values.push_back(token);
	}
	if (this->_name.empty())
		throw DirectiveException();
	LOG_DEB("Directive constructor called");
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
	return  (RED "Error creating Directive !" RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Directive &src_object )
{
	out	<< GREEN << "DIRECTIVE INFORMATION" << std::endl
		<< "name: " << src_object.getName()
		<< " => [" << src_object.getAllValue() << "]" << std::endl
		<< RESET;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef TEST

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