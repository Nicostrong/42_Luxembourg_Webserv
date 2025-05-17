/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_e.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:29:35 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:51:40 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Server.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsing error with data
 */
Server::ParsingError::ParsingError( const std::string &data ) throw()
{
	this->_msg = RED"[ERROR] Parsing data: " + data + RESET;
	return ;
}

/*
 *	Destructor for ParsingError
 */
Server::ParsingError::~ParsingError( void ) throw()
{
	return ;
}

/*
 *	Error parsing file.conf
 */
const char*		Server::ParsingError::what() const throw()
{
	return (this->_msg.c_str());
}

/*
 *	Port value exception
 */
const char*		Server::PortValueException::what() const throw()
{
	return (RED "[ERROR] Value of port not correct !" RESET);
}