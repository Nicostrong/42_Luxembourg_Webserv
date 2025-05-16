/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_gs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:35:34 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 10:28:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/*******************************************************************************
 *							SETTER PRIVATE									   *
 ******************************************************************************/

/*
 *	Transform the string in size_t type for the port and check the value
 */
void			Server::setPort( std::list<std::string> datalist )
{
	std::list<size_t>						lPorts;
	std::list<std::string>::iterator		it;
	
	for (it = datalist.begin(); it != datalist.end(); ++it)
	{
		size_t					port;
		std::stringstream		ss(*it);

		if (!(ss >> port))
			throw ParsingError(*it);
		if (port <= 0 || port > 65535)
			throw PortValueException();
		lPorts.push_back(port);
	}
	this->_lPorts = lPorts;
	return ;
}

/*
 *	Transform the string in size_t and apply a factor for the final value
 */
void			Server::setMaxSizeBody( std::string data )
{
	size_t					value;
	size_t					factor = 1;
	char					unit = 0;
	std::string				numberPart;
	std::istringstream		stream(data);

	if (data.empty())
		throw ParsingError(data);
	if (!(stream >> value))
		throw ParsingError(data);
	if (stream >> unit)
	{
		if (unit == 'M' || unit == 'm')
			factor = 1024 * 1024;
		else if (unit == 'K' || unit == 'k')
			factor = 1024;
	}
	this->_maxSizeBody = value * factor;
	return ;
}

/*
 *	Transform the string in int type for the number of client can connect
 */
void			Server::setMaxClient( std::string data )
{
	int						clients;
	std::stringstream		ss(data);
	
	if (!(ss >> clients))
			throw ParsingError(data);
	if (clients <= 0)
		clients = 10;
	this->_maxClient = clients;
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _maxConnectionClient value
 */
const int&									Server::getMaxClient( void ) const
{
	return (this->_maxClient);
}

/*
 *	get _port value
 */
const std::list<size_t>&					Server::getPortList( void ) const
{
	return (this->_lPorts);
}

/*
 *	get _serverIp value
 */
const std::string&							Server::getServerIp( void ) const
{
	return (this->_serverIp);
}

/*
 *	get _maxSizeBody value
 */
const size_t&								Server::getMaxSizeBody( void ) const
{
	return (this->_maxSizeBody);
}

/*
 *	get _lHost value
 */

const std::list<std::string>&				Server::getHost( void ) const
{
	return (this->_lHost);
}

/*
 *	get _path value
 */
const std::string&							Server::getPath( void ) const
{
	return (this->_path);
}

/*
 *	get _index value
 */
const std::string&							Server::getIndex( void ) const
{
	return (this->_index);
}

/*
 *	get _mError value
 */
const std::map<size_t, std::string>&		Server::getMapError( void ) const
{
	return (this->_mError);
}


/*
 *	get all Location object of the server
 */
const std::map<std::string, Location *>		Server::getAllLocation( void ) const
{
	return (this->_mLocations);
}

/*
 *	get all value of Location
 */

const Location&			Server::getLocations( std::string path ) const
{
	std::map<std::string, Location*>::const_iterator		it;
	
	it = _mLocations.find(path);
	if (it != _mLocations.end())
		return (*(it->second));
	throw std::runtime_error("Location not found");
}

/*
 *	return the path of the code error in argument
 */
const std::string&		Server::getPathError( size_t error_code ) const
{
	std::map<size_t, std::string>::const_iterator		it;
	
	it = _mError.find(error_code);
	if (it != _mError.end())
		return (it->second);
	throw std::runtime_error("Error code not found");
}
