/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fullServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:28:13 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 14:12:27 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "../includes/HandleConfig.hpp"
#include "../includes/ParserServerConfig.hpp"
#include "../includes/ServerManager.hpp"

int	main( void )
{
	try
	{
		ParserServerConfig					pc("./good_config/good_1.conf");
		EventMonitoring						em;
		ServerManager						sm(pc.getListTokens(), em);

		assert(sm.getNbServer() == 3);
		std::cout << "✅ [OK] Number of servers parsed correctly" << std::endl;
		
		Server* s1 = sm.getServer(8080);
		std::cout << *s1 << std::endl;
		assert(s1 != NULL);
		std::cout << "✅ [OK] Check if Server isn't NULL" << std::endl;
		assert(s1->getPort() == 8080);
		std::cout << "✅ [OK] Check port == 8080" << std::endl;
		//assert(*s1->getHost() == "localhost");
		//std::cout << "✅ [OK] Check name of server" << std::endl;
		assert(s1->getPath() == "./www/html");
		std::cout << "✅ [OK] Check the path" << std::endl;
		assert(s1->getIndex() == "index.html");
		std::cout << "✅ [OK] Check the root" << std::endl;
		assert(s1->getMaxClient() == 10);
		std::cout << "✅ [OK] Check numberber of client" << std::endl;
		assert(s1->getMaxSizeBody() == 5 * 1024 * 1024);
		std::cout << "✅ [OK] Check size of body" << std::endl;
		assert(s1->checkUri("/"));
		std::cout << "✅ [OK] Check if uri '/' existe" << std::endl;
		assert(s1->checkUri("/toto"));
		std::cout << "✅ [OK] Check if uri '/toto' existe" << std::endl;
		std::cout << "✅ [OK] Server 8080 config valid" << std::endl;
		
		Server* s2 = sm.getServer(443);
		std::cout << *s2 << std::endl;
		assert(s2 != NULL);
		std::cout << "✅ [OK] Check if Server isn't NULL" << std::endl;
		assert(s2->checkUri("/images/toto"));
		std::cout << "✅ [OK] Check if uri '/images/toto' existe" << std::endl;
		assert(s2->checkUri("/downloads"));
		std::cout << "✅ [OK] Check if uri '/downloads' existe" << std::endl;
		assert(s2->checkMethod("/images", "GET"));
		std::cout << "✅ [OK] Check if uri '/images' existe" << std::endl;
		assert(!s2->checkMethod("/images", "POST"));
		std::cout << "✅ [OK] Check on uri '/images' if POST is allow" << std::endl;
		std::cout << "✅ [OK] Server 443 location/method valid" << std::endl;
	
		Server* s3 = sm.getServer(21);
		std::cout << *s3 << std::endl;
		assert(s3 != NULL);
		std::cout << "✅ [OK] Check if Server isn't NULL" << std::endl;
		assert(s3->checkUri("/deleteable"));
		std::cout << "✅ [OK] Check if uri '/deleteable' existe" << std::endl;
		assert(s3->checkMethod("/deleteable", "DELETE"));
		std::cout << "✅ [OK] Check on uri '/deleteable' if DELETE is allow" << std::endl;
		assert(s3->checkMethod("/redirect", "GET"));
		std::cout << "✅ [OK] Check on uri '/redirect' if GET is allow" << std::endl;
		std::cout << "✅ [OK] Server 21 config valid" << std::endl;
		
		assert(s1->getPathError(403) == "./errors/403.html");
		std::cout << "✅ [OK] Check if the path of error_403 is correct" << std::endl;
		assert(s1->getPathError(404) == "./errors/404.html");
		std::cout << "✅ [OK] Check if the path of error_404 is correct" << std::endl;
		assert(s1->getPathError(418) == "./errors/418.html");
		std::cout << "✅ [OK] Check if the path of error_418 is correct" << std::endl;
		std::cout << "✅ [OK] Error page paths valid" << std::endl;

		std::cout << "✅✅✅✅✅✅✅ [OK] ALL IS ALLRIGHT ✅✅✅✅✅✅✅" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}