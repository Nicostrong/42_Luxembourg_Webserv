/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 11:06:37 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/MethodHTTP.hpp"
#include "../../includes/Token.hpp"

/*******************************************************************************
 *							INITIALISATION CLASS							   *
 ******************************************************************************/

std::set<std::string>		MethodHTTP::_validMethods = MethodHTTP::initMethods();

/*
 *	Initialise the set of valid methods
 */
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
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor when no info on Location block for the allow methods
 */
MethodHTTP::MethodHTTP( void ) { initDefault(); }

/*
 *	Constructor with tokens of allow methods
 */
MethodHTTP::MethodHTTP( Token*& tokens )
{
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
	this->_allowed.clear();
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	By default all method are allowed
 */
void	MethodHTTP::initDefault( void )
{
	this->_allowed.insert(MethodHTTP::_validMethods.begin(), MethodHTTP::_validMethods.end());
	return ;
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
 *								METHOD 										   *
 ******************************************************************************/

/*
 *	Check if the method is allowed
 */
bool	MethodHTTP::isAllowed( const std::string &method ) const
{
	return (this->_allowed.find(method) != this->_allowed.end());
}

/*
 *	Check if the method is a valid method
 */
bool	MethodHTTP::isMethod( const std::string &method )
{
	return (MethodHTTP::_validMethods.find(method) != MethodHTTP::_validMethods.end());
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