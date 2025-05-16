/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location_m.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:52:21 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:53:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Location.hpp"
#include "../../includes/Token.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Read all Location tokens and create the Location object
 */
void						Location::createLocation( Token*& tokens )
{
	this->_path = tokens->getValue();
	while (tokens && tokens->getType() != Token::LOC_BLK_E)
	{
		if (tokens->getType() == Token::DIR_K)
			this->_lDirectives.push_back(new Directive(tokens));
		else if (tokens->getType() == Token::HTTP_K && !this->_method)
			this->_method = new MethodHTTP(tokens);
		else if (tokens->getType() == Token::CGI_K)
			this->_lCGIDirectives.push_back(new CGIDirective(tokens));
		tokens = tokens->getNext();
	}
	return ;
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Location const &src_object )
{
	std::list<Directive*>::const_iterator			itDir;
	std::list<CGIDirective*>::const_iterator		itCGI;

	out	<< YELLOW << "------------- LOCATION BLOCK -------------" << RESET << std::endl
		<< YELLOW << "Name:\n\t" << src_object.getPath() << RESET << std::endl;
	if (src_object.getMethod() != NULL)
		out << YELLOW << *src_object.getMethod() << RESET << std::endl;
	if (!src_object.getDirectives().empty())
		for (itDir = src_object.getDirectives().begin(); itDir != src_object.getDirectives().end(); ++itDir)
			out << **itDir;
	if (!src_object.getCGIDirectives().empty())
		for (itCGI = src_object.getCGIDirectives().begin(); itCGI != src_object.getCGIDirectives().end(); ++itCGI)
			out << **itCGI;
	out << YELLOW << "------------------------------------------" << RESET << std::endl;
	return (out);
}