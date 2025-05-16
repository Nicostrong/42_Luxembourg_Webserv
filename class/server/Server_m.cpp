/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_m.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:19:37 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:30:38 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/


/*******************************************************************************
 *								CHECKER										   *
 ******************************************************************************/

/*
 *	Check if the uri exist in the map of Location
 */
bool							Server::checkUri( std::string uri )
{
	std::map<std::string, Location*>::iterator		it;

	for ( it = this->_mLocations.begin(); it != this->_mLocations.end(); ++it)
	{
		if (it->second->isMatching(uri))
			return true;
	}
	return (false);
}

/*
 *	Check if the host exist in the list of host of the server
 */
bool		Server::matchHost( const std::string& host ) const
{
	return (matchServerName(host) || matchServerNameWildcard(host));
}

/*
 *	Check if a method is allowed in a Location scope
 */
bool	Server::checkMethod( std::string uri, std::string method )
{
	const Location*		location = getMatchingLoc(uri);

	if (location && location->getMethod())
		return (location->getMethod()->isAllowed(method));
	return (false);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Server const &src_object )
{
	std::map<size_t, std::string>::const_iterator		it;
	std::map<size_t, std::string>						mError;
	const std::map<std::string, Location *>				loc = src_object.getAllLocation();
	const std::list<std::string>&						hosts = src_object.getHost();
	std::list<std::string>::const_iterator				itHost;
	const std::list<size_t>&							ports = src_object.getPortList();
	std::list<size_t>::const_iterator					itPort;
	
	mError = src_object.getMapError();
	
	out	<< GREEN << "================= SERVER CONFIG =================" << RESET << std::endl
		<< GREEN << "Name:" << std::endl;
		
	for (itHost = hosts.begin(); itHost != hosts.end(); ++itHost)
		out << "\t- " << *itHost << std::endl;

	out << RESET <<std::endl
		<< GREEN << "Listen adress:\n\t" << src_object.getServerIp() << RESET << std::endl
		<< GREEN << "Listen port:" << RESET << std::endl;
	for ( itPort = ports.begin(); itPort != ports.end(); ++itPort)
   		out << GREEN << "\t- " << *itPort << RESET << std::endl;
	out << GREEN << "Root path:\n\t" << src_object.getPath() << RESET << std::endl
		<< GREEN << "Index file:\n\t" << src_object.getIndex() << RESET << std::endl
		<< GREEN << "Max connection client:\n\t" << src_object.getMaxClient() << RESET << std::endl
		<< GREEN << "Max size of body:\n\t" << src_object.getMaxSizeBody() << " bytes." << RESET << std::endl
		<< GREEN << "Error pages:" << RESET << std::endl;
	
	for (it = mError.begin(); it != mError.end(); ++it)
		out << GREEN << "\t" << it->first << " => " << it->second << RESET << std::endl;
	
	out << GREEN << "Locations:" << RESET << std::endl;	
	for (std::map<std::string, Location *>::const_iterator it = loc.begin(); it != loc.end(); ++it)
		out << *it->second << RESET << std::endl;
	out	<< GREEN << "=================== END SERVER ==================" << RESET << std::endl;
	return (out);
}