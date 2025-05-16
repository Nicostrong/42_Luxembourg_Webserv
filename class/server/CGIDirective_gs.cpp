/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective_gs.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:57:29 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:57:45 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGIDirective.hpp"

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