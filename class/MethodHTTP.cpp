/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHTTP.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/28 12:35:37 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MethodHTTP.hpp"

std::set<std::string>	MethodHTTP::_validMethods = MethodHTTP::initValidMethods();

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
MethodHTTP::MethodHTTP( void )
{
	LOG_DEB("MethodHTTP constructor witout argument called");
	return ;
}

/*
 *	Default constructor with argument
 */
MethodHTTP::MethodHTTP( const std::string &data )
{
	parse(data);
	LOG_DEB("MethodHTTP constructor with argument called");
	return ;
}

/*
*	Destructor
*/
MethodHTTP::~MethodHTTP( void )
{
	LOG_DEB("MethodHTTP destructor called");
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
	{
		this->_allowed = src_object._allowed;
		this->_denied = src_object._denied;
	}
	return (*this);
}

/*
 *	Parser of data
 */
void	MethodHTTP::parse( const std::string &data )
{
	bool				isDenyBlock = false;
	std::string			word;
	std::istringstream	stream(data);

	this->_allowed.clear();
	this->_denied.clear();
	while (stream >> word && word != "}")
	{
		if (!word.empty() && word[word.size() - 1] == ';')
			word.erase(word.size() - 1);
		if (word == "limit_except" || word == "allow" || word == "{")
			continue ;
		if (word == "deny")
		{
			isDenyBlock = true;
			continue ;
		}
		if(word == "all")
		{
			if (isDenyBlock)
			{
				std::set<std::string>::const_iterator	it;

				this->_denied.insert(this->_validMethods.begin(), this->_validMethods.end());
				for (it = this->_allowed.begin(); it != this->_allowed.end(); ++it)
					this->_denied.erase(*it);
			}
			else
			{
				std::set<std::string>::const_iterator	it;

				this->_allowed.insert(this->_validMethods.begin(), this->_validMethods.end());
				for (it = this->_denied.begin(); it != this->_denied.end(); ++it)
					this->_allowed.erase(*it);
			}
			continue;
		}
		if (!isMethod(word))
			throw MethodUnknow(word);
		if (isDenyBlock)
		{
			this->_denied.insert(word);
			this->_allowed.erase(word);
		}
		else
		{
			this->_allowed.insert(word);
			this->_denied.erase(word);
		}
	}
	LOG_DEB("MethodHTTP parse called");
	return ;
}

/*
 *	Initialisation of all methods value valide
 */
std::set<std::string>	MethodHTTP::initValidMethods( void )
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
bool	MethodHTTP::isMethod( const std::string &method ) const
{
	LOG_DEB("Checking if " + method + " is a valid method");
	return (this->_validMethods.find(method) != this->_validMethods.end());
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

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

/*
 *	Add a method on the array denied methods
 */
void	MethodHTTP::deny( const std::string &method )
{
	if (!isMethod(method))
		throw MethodUnknow(method);
	this->_denied.insert(method);
	LOG_DEB("new method add on  denied methods");
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

/*
 *	get all Methods denied
 */
std::string		MethodHTTP::getDenied( void ) const
{
	std::string								ret;
	std::set<std::string>::const_iterator	it;

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
bool	MethodHTTP::isAllowed( const std::string &method ) const
{
	return (this->_allowed.find(method) != this->_allowed.end());
}

/*
 *	Check if the method is denied
 */
bool	MethodHTTP::isDenied( const std::string &method ) const
{
	return (this->_denied.find(method) != this->_denied.end());
}

/*
 *	Clear the both array on the object
 */
void	MethodHTTP::clear( void )
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
 *	Creation class Exception for parsong error with data
 */
MethodHTTP::MethodUnknow::MethodUnknow( const std::string &method ) throw()
{
	this->_msg = RED"Error method unknow: " + method + RESET;
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
		<< "Methods Denied: [" << src_object.getDenied() << "]" << std::endl
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
		assert(method.getDenied().empty());
		std::cout << method << std::endl;
		std::cout << "✅  [OK] Empty MethodHTTP parsed correctly" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void test_deny_all( void )
{
	try
	{
		std::string								config = "{\n\tdeny\t\t\tall;\n}";
		MethodHTTP								method(config);

		std::cout << method << std::endl;
		std::cout << "✅  [OK] Deny all parsed correctly" << std::endl;
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

void test_get_deny_all( void )
{
	try
	{
		std::string								config = "GET\t{\n\tdeny\t\t\tall;\n}";
		MethodHTTP								method(config);

		std::cout << method << std::endl;
		assert(!method.isDenied("GET"));
		std::cout << "✅  [OK] GET OK and Deny all parsed correctly" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

void test_allow_all_deny_get( void )
{
	try
	{
		std::string								config = "all\t{\n\tdeny\t\tGET;\n};";
		MethodHTTP								method(config);

		std::cout << method << std::endl;
		assert(!method.isAllowed("GET"));
		std::cout << "✅  [OK] Allow all deny GET parsed correctly" << std::endl;
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
		method.deny("DELETE");

		assert(method.isAllowed("GET"));
		assert(method.isAllowed("POST"));
		assert(method.isDenied("DELETE"));
		assert(!method.isAllowed("DELETE"));
		assert(!method.isDenied("PUT"));
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
	std::cout << BLUE << "DENY ALL TEST" << RESET << std::endl;
	test_deny_all();
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