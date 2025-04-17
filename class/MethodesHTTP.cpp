/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodesHTTP.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 16:16:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MethodesHTTP.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
MethodesHTTP::MethodesHTTP( void )
{
	this->_validMethodes = MethodesHTTP::initValidMethodes();
	LOG_DEB("MethodesHTTP constructor called");
	return ;
}

/*
*	Destructor
*/
MethodesHTTP::~MethodesHTTP( void )
{
	LOG_DEB("MethodesHTTP destructor called");
	return ;
}

/*
 *	Initialisation of all methodes value valide
 */
std::set<std::string>	MethodesHTTP::initValidMethodes( void )
{
	std::set<std::string>	m;

	m.insert("GET");
	m.insert("POST");
	m.insert("PUT");
	m.insert("DELETE");
	m.insert("PATCH");
	m.insert("OPTIONS");
	m.insert("HEAD");

	return (m);
}

/*
 *	Check if the method is a valid methode
 */
bool	MethodesHTTP::isMethode( const std::string &methode ) const
{
	LOG_DEB("Checking if " + methode + " is a valid method");
	return (this->_validMethodes.find(methode) != this->_validMethodes.end());
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

/*
 *	Add a methode on the array allowed methodes
 */
void	MethodesHTTP::allow( const std::string &methode )
{
	if (!isMethode(methode))
		throw MethodeUnknowException();
	this->_allowed.insert(methode);
	LOG_DEB("new methode add on allowed method");
	return ;
}

/*
 *	Add a methode on the array denied methodes
 */
void	MethodesHTTP::deny( const std::string &methode )
{
	if (!isMethode(methode))
		throw MethodeUnknowException();
	this->_denied.insert(methode);
	LOG_DEB("new methode add on  denied method");
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get all Methodes allowed
 */
std::string		MethodesHTTP::getAllowed( void ) const
{
	std::string						ret;
	std::set<std::string>::iterator	it;

	for ( it = this->_allowed.begin(); it != this->_allowed.end(); ++it)
	{
		ret += *it;
		if (it != this->_allowed.end())
			ret += ", ";
	}
	return (ret);
}

/*
 *	get all Methodes denied
 */
std::string		MethodesHTTP::getDenied( void ) const
{
	std::string						ret;
	std::set<std::string>::iterator	it;

	for ( it = this->_denied.begin(); it != this->_denied.end(); ++it)
	{
		ret += *it;
		if (it != this->_denied.end())
			ret += ", ";
	}
	return (ret);
}

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/


/*
 *	Check if the methode is allowed
 */
bool	MethodesHTTP::isAllowed( const std::string &methode ) const
{
	return (this->_allowed.find(methode) != this->_allowed.end());
}

/*
 *	Check if the methode is denied
 */
bool	MethodesHTTP::isDenied( const std::string &methode ) const
{
	return (this->_denied.find(methode) != this->_denied.end());
}

/*
 *	Clear the both array on the object
 */
void	MethodesHTTP::clear( void )
{
	this->_allowed.clear();
	this->_denied.clear();
	LOG_DEB("The both array are cleared");
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Exception for unknow methode
 */
const char	*MethodesHTTP::MethodeUnknowException::what() const throw()
{
	return ("Unknown HTTP method specified");
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, MethodesHTTP const &src_object )
{
	out	<< GREEN << "METHODES INFORMATION"
		<< "\nMethodes Allow:\n" << src_object.getAllowed()
		<< "\nMethodes Denied:\n" << src_object.getDenied()
		<< RESET;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef TEST

#include "../includes/Server.hpp"
 
int	main( void )
{
	MethodesHTTP	obj;
	
	try
	{
		obj.allow("GET");
		obj.deny("POST");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << obj << std::endl;
	try
	{
		obj.allow("toto");
		obj.deny("Franck");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}

#endif