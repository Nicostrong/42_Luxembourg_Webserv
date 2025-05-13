/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:23:08 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MethodHTTP.hpp"
#include "../includes/Token.hpp"

std::set<std::string>		MethodHTTP::_validMethods = MethodHTTP::initMethods();

std::set<std::string>		MethodHTTP::initMethods( void )
{
	std::set<std::string>		methods;

	methods.insert("GET");
	methods.insert("POST");
	methods.insert("PUT");
	methods.insert("DELETE");
	methods.insert("PATCH");
	methods.insert("OPTIONS");
	methods.insert("HEAD");
	return (methods);
}

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
MethodHTTP::MethodHTTP( void )
{
	initDefault();
	return ;
}

/*
 *	Constructor with tokens
 */
MethodHTTP::MethodHTTP( Token* tokens )
{
	LOG_DEB("MethodHTTP constructor with tokens called");
	initDefault();
	while (tokens && tokens->getType() != Token::SEMICOLON)
	{
		if (tokens->getType() == Token::HTTP_V)
		{
			if (tokens->getValue() == "all")
				allowAll();
			else
				allow(tokens->getValue());
		}
		tokens = tokens->getNext();
	}
	return ;
}

/*
*	Destructor
*/
MethodHTTP::~MethodHTTP( void )
{
	LOG_DEB("MethodHTTP destructor called");
	this->_allowed.clear();
	return ;
}

/*
 *	Copy constructor
 */
MethodHTTP::MethodHTTP( const MethodHTTP &src_object )
{
	*this = src_object;
	return ;
}

/*
 *	Copy assignment operator
 */
MethodHTTP		&MethodHTTP::operator=( const MethodHTTP &src_object )
{
	if (this != &src_object)
		this->_allowed = src_object._allowed;
	return (*this);
}

/*
 *	Check if the method is a valid methode
 */
bool	MethodHTTP::isMethod( const std::string &method )
{
	LOG_DEB("Checking if " + method + " is a valid method");
	return (MethodHTTP::_validMethods.find(method) != MethodHTTP::_validMethods.end());
}

/*
 *	By default all method are allowed
 */
void	MethodHTTP::initDefault( void )
{
	this->_allowed.insert(MethodHTTP::_validMethods.begin(), MethodHTTP::_validMethods.end());
	LOG_DEB("All HTTP methods added to _allowed by default");
	return ;
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

/*
 *	Allow all method
 */
void	MethodHTTP::allowAll( void )
{
	this->_allowed.insert(MethodHTTP::_validMethods.begin(), MethodHTTP::_validMethods.end());
	LOG_DEB("All method are allowed methods");
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
	LOG_DEB("new method add on allowed methods");
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get all Methods allowed
 */
std::string		MethodHTTP::getAllowed( void ) const
{
	std::string								ret;
	std::set<std::string>::const_iterator	it;

	for ( it = this->_allowed.begin(); it != this->_allowed.end(); ++it)
	{
		ret += *it;
		if (it != this->_allowed.end())
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
bool	MethodHTTP::isAllowed( const std::string &method ) const
{
	return (this->_allowed.find(method) != this->_allowed.end());
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsong error with data
 */
MethodHTTP::MethodUnknow::MethodUnknow( const std::string &method ) throw()
{
	this->_msg = RED"[ERROR] Method unknow: " + method + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
MethodHTTP::MethodUnknow::~MethodUnknow( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char		*MethodHTTP::MethodUnknow::what() const throw()
{
	return (this->_msg.c_str());
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
		<< "Methods Allow: [" << src_object.getAllowed() << "]" << std::endl
		<< "------------------------------------------" <<RESET;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef MET
# include <cassert>

void test_empty_block( void )
{
	try
	{
		std::string	config = "";
		MethodHTTP	method(config);

		assert(method.getAllowed().empty());
		std::cout << method << std::endl;
		std::cout << "✅  [OK] Empty MethodHTTP parsed correctly" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void test_allow_all( void )
{
	try
	{
		std::string								config = "all;";
		MethodHTTP								method(config);

		std::cout << method << std::endl;
		std::cout << "✅  [OK] Allow all parsed correctly" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void test_manual_allow_deny( void )
{
	try
	{
		MethodHTTP	method;

		method.allow("GET");
		method.allow("POST");

		assert(method.isAllowed("GET"));
		assert(method.isAllowed("POST"));
		std::cout << method << std::endl;
		std::cout << "✅  [OK] Manual allow/deny works" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void test_unknown_method( const std::string &method )
{
	try
	{
		MethodHTTP	met;

		met.allow(method);
		std::cout << met << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

int main( void )
{
	std::cout << BLUE << "EMPTY BLOCK TEST" << RESET << std::endl;
	test_empty_block();
	std::cout << BLUE << "ALLOW ALL TEST" << RESET << std::endl;
	test_allow_all();
	std::cout << BLUE << "GET OK AND DENY ALL TEST" << RESET << std::endl;
	test_get_deny_all();
	std::cout << BLUE << "ALLOW ALL DENY GET TEST" << RESET << std::endl;
	test_allow_all_deny_get();
	std::cout << BLUE << "MANUAL ALLOW/DENY TEST" << RESET << std::endl;
	test_manual_allow_deny();
	std::cout << BLUE << "UNKNOWN METHOD TEST" << RESET << std::endl;
	test_unknown_method("UNKNOWN");
	test_unknown_method("TATA");
	test_unknown_method("FLAVIANT");
	test_unknown_method("GIGI");
	std::cout << "✅  [OK]  All MethodHTTP tests passed." << std::endl;
	return (0);
}

#endif