/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodesHTTP.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 16:14:23 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MethodesHTTP.hpp"

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


bool	MethodesHTTP::isMethode( const std::string &methode ) const
{
	LOG_DEB("Checking of valid methode");
    return (this->_validMethodes.find(methode) != this->_validMethodes.end());
}

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

/*
 *	Exception for unknow methode
 */
const char	*MethodesHTTP::MethodeUnknowException::what() const throw()
{
    return ("Unknown HTTP method specified");
}
