/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 10:20:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Server constructor with tokens in argument
 */
Server::Server( Token*& serverTokensConfig, EventMonitoring &eventMonitoring) 
	: _maxClient(0), _serverSocket(0), _maxSizeBody(0), _path("/www/html"),
	_index("index.html"), _serverIp(SERVER_IP), _em(eventMonitoring)
{
	try
	{
		createServer(serverTokensConfig);
		setAttributs();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	Destructor Server delete all pointer of Location and Directive object
 */
Server::~Server( void )
{
	std::list<Directive *>::iterator				itDir;
	std::map<std::string, Location *>::iterator		itLoc;

	cleanup();
	for ( itDir = this->_lDirectives.begin(); itDir != this->_lDirectives.end(); ++itDir)
		delete *itDir;
	this->_lDirectives.clear();
	for ( itLoc = this->_mLocations.begin(); itLoc != this->_mLocations.end(); ++itLoc)
		delete itLoc->second;
	this->_mLocations.clear();
	return ;
}


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
 *	Check if the uri exist in the map of Location and return a const pointer of
 *	the Location object
 */
const Location*					Server::getMatchingLoc( const std::string& uri )
{
	std::map<std::string, Location *>::iterator		it;
	Location* 										bestMatch = NULL;
	
	for (it = this->_mLocations.begin(); it != this->_mLocations.end(); it++)
	{
		if(it->second->isMatching(uri))
		{
			if (!bestMatch || 
					bestMatch->getPath().size() < it->second->getPath().size())
				bestMatch = it->second;
		}
	}
	return (bestMatch);
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
const char		*Server::ParsingError::what() const throw()
{
	return (this->_msg.c_str());
}

/*
 *	Port value exception
 */
const char		*Server::PortValueException::what() const throw()
{
	return (RED "[ERROR] Value of port not correct !" RESET);
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
	std::list<std::string>::const_iterator				itHost = hosts.begin();
	
	mError = src_object.getMapError();
	
	out	<< GREEN << "================= SERVER CONFIG =================" << RESET << std::endl
		<< GREEN << "Name:" << std::endl;
		
	while (itHost != hosts.end())
		out << "\t\t- " << *itHost << std::endl;

	out << RESET <<std::endl
		<< GREEN << "Listen adress:\t\t" << src_object.getServerIp() << RESET << std::endl
		<< GREEN << "Listen port:\t\t" << src_object.getPort() << RESET << std::endl
		<< GREEN << "Root path:\t\t" << src_object.getPath() << RESET << std::endl
		<< GREEN << "Index file:\t\t" << src_object.getIndex() << RESET << std::endl
		<< GREEN << "Max connection client:\t" << src_object.getMaxClient() << RESET << std::endl
		<< GREEN << "Max size of body:\t" << src_object.getMaxSizeBody() << " bytes." << RESET << std::endl
		<< GREEN << "Error pages:" << RESET << std::endl;
	
	for (it = mError.begin(); it != mError.end(); ++it)
		out << GREEN << "\t" << it->first << " => " << it->second << RESET << std::endl;
	
	out << GREEN << "Locations:" << RESET << std::endl;	
	for (std::map<std::string, Location *>::const_iterator it = loc.begin(); it != loc.end(); ++it)
		out << *it->second << RESET << std::endl;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef SER

# include <cassert>
# include "../includes/HandleConfig.hpp"

int	main( void )
{
	HandleConfig	hg("webserv.conf");

	try
	{
		Server	s(hg.getwebconfMap());
		assert(s.getPort() == 8080);
		std::cout << "✅ [OK] get Port test passed." << std::endl;
		assert(s.getAdress() == "127.0.0.1");
		std::cout << "✅ [OK] get Adress test passed." << std::endl;
		assert(s.getName() == "localhost");
		std::cout << "✅ [OK] get Name test passed." << std::endl;
		assert(s.getPath() == "./www/html");
		std::cout << "✅ [OK] get Path test passed." << std::endl;
		assert(s.getMaxSizeBody() == 5242880);
		std::cout << "✅ [OK] get MaxSizeBody test passed." << std::endl;
		assert(s.getIndex() == "index.html");
		std::cout << "✅ [OK] get Index test passed." << std::endl;
		std::cout << s << std::endl;
		std::cout << "✅ [OK] Serverbasic config test passed." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}

#endif