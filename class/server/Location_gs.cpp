/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location_gs.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:07:35 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/06 14:34:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"
#include "../../includes/server/Location.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
const std::string&					Location::getPath( void ) const
{
	return (this->_path);
}

/*
 *	get the path of CGIDirective of the extension
 */
const std::string&					Location::getCGIPath( const std::string& extension ) const
{
	std::list<CGIDirective*>					CGILst = getCGIDirectives();
	std::list<CGIDirective*>::const_iterator	itCGILst;

	if (!isCGICDir(extension))
		return ("");
	for (itCGILst = CGILst.begin(); itCGILst != CGILst.end(); ++itCGILst)
		if ((*itCGILst)->getExtension() == extension)
			return ((*itCGILst)->getPath());
	return ("");
}

/*
 *	getMethod return the pointer of MethodHTTP for this Location
 */
const MethodHTTP*					Location::getMethod( void ) const
{
	return (this->_method);
}

/*
 *	getDirectives return the list of directives
 */
const std::list<Directive*>&		Location::getDirectives( void ) const
{
	return (this->_lDirectives);
}

/*
 *	getCGIDirectives return the list of CGIDirectives
 */
const std::list<CGIDirective*>&		Location::getCGIDirectives( void ) const
{
	return (this->_lCGIDirectives);
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