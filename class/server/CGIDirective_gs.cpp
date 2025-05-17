/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective_gs.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:57:29 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:49:12 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/CGIDirective.hpp"

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _extension value
 */
const std::string&		CGIDirective::getExtension( void ) const
{
	if (this->_extension.empty())
		throw FieldsEmpty();
	return (this->_extension);
}

/*
 *	get _path value
 */
const std::string&		CGIDirective::getPath( ) const
{
	if (this->_path.empty())
		throw FieldsEmpty();
	return (this->_path);
}