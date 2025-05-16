/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_m.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:32 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:56:57 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Directive.hpp"

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, const Directive &src_object )
{
	const std::list<std::string>&				values = src_object.getValues();
	std::list<std::string>::const_iterator		it;
	bool										first = true;

	out	<< BLUE << "------------- DIRECTIVE BLOCK -------------" << std::endl
		<< "name:\n\t" << src_object.getKey()
		<< " => [";
	
	for (it = values.begin(); it != values.end(); ++it)
	{
		if (!first)
			out << ", ";
		out << *it;
		first = false;
	}
	out << "]" << std::endl
		<< "------------------------------------------"	<< RESET << std::endl;
	return (out);
}