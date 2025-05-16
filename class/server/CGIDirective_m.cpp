/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective_m.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:58:32 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:58:53 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGIDirective.hpp"

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream& out, const CGIDirective& src_object )
{
	out	<< BLUE << "------------- CGIDIRECTIVE BLOCK -------------" << std::endl
		<< "name:\n\t" << src_object.getExtension()
		<< " => [" << src_object.getPath() << "]" << std::endl
		<< "------------------------------------------"	<< RESET << std::endl;
	return (out);
}