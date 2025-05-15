/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig_e.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:28:30 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 08:30:53 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ParserServerConfig.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error while opening file config
 */
const char		*ParserServerConfig::FileError::what() const throw()
{
	return (RED "[ERROR FILE] Opening file server config fail" RESET);
}

/*
 *	Error bad extension file
 */
const char		*ParserServerConfig::BadExtensionFile::what() const throw()
{
	return (RED "[ERROR FILE] Bad extension file." RESET);
}

/*
 *	Error empty file config
 */
const char		*ParserServerConfig::EmptyConfigError::what() const throw()
{
	return (RED "[ERROR FILE] Empty file config or not valid." RESET);
}

/*
 *	Error while getting the server map
 */
const char		*ParserServerConfig::GetServerMapError::what() const throw()
{
	return (RED "[ERROR] Index out of range in getServer" RESET);
}