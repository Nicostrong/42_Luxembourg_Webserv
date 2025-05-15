/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig_e.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:28:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 13:14:29 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ParserServerConfig.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error while opening file config
 */
const char*		ParserServerConfig::FileError::what() const throw()
{
	return (RED "[ERROR FILE] Opening file server config fail" RESET);
}

/*
 *	Error bad extension file
 */
const char*		ParserServerConfig::BadExtensionFile::what() const throw()
{
	return (RED "[ERROR FILE] Bad extension file." RESET);
}

/*
 *	Error empty file config
 */
const char*		ParserServerConfig::EmptyConfigError::what() const throw()
{
	return (RED "[ERROR FILE] Empty file config or not valid." RESET);
}

/*
 *	Error while getting the server map
 */
const char*		ParserServerConfig::GetServerMapError::what() const throw()
{
	return (RED "[ERROR] Index out of range in getServer" RESET);
}