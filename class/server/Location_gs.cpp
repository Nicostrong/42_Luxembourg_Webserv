/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location_gs.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:07:35 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 11:09:45 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Location.hpp"
#include "../../includes/Token.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
const std::string&				Location::getPath( void ) const
{
	return (this->_path);
}

/*
 *	getMethod return the pointer of MethodHTTP for this Location
 */
const MethodHTTP*				Location::getMethod( void ) const
{
	return (this->_method);
}

/*
 *	getDirectives return the list of directives
 */
const std::list<Directive *>&	Location::getDirectives( void ) const
{
	return (this->_lDirectives);
}

/*
 *	Check if the location can match to a requested uri
 */
bool		Location::isMatching( const std::string& uri ) const
{
	if (this->_path.empty() || uri.empty())
		return (false);
		
	if (uri.length() < this->_path.size() || 
		!std::equal(this->_path.begin(), this->_path.end(), uri.begin()))
		return (false);

	if (this->_path.at(this->_path.size() - 1) != '/')
	{
		size_t s = uri.find('/', this->_path.size());
		if (s == this->_path.size() || s == std::string::npos)
			return (true);
		return (false);
	}
	
	return (true);
}

/*
 * Find a directive in the directive list
 */
const Directive*		Location::findDirective( const std::string& name ) const
{
	std::list<Directive*>::const_iterator it;

	for (it = this->_lDirectives.begin(); it != this->_lDirectives.end(); it++)
	{
		if ((*it)->getKey() == name)
			return (*it);
	}
	return (NULL);
}

/*
 * Find all directives in the directive list
 */
const std::list<Directive*>	Location::findDirectives( const std::string& name ) const
{
	std::list<Directive*>::const_iterator it;
	std::list<Directive*> directives;

	for (it = this->_lDirectives.begin(); it != this->_lDirectives.end(); it++)
	{
		if ((*it)->getKey() == name)
			directives.push_back(*it);
	}
	return (directives);
}