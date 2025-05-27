/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/27 08:56:49 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Server.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Server constructor with tokens in argument
 */
Server::Server( Token*& serverTokensConfig, EventMonitoring &eventMonitoring) 
	: _maxClient(1), _serverSocket(0), _maxSizeBody(1024), _path("/www/html"),
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