/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fullServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:28:13 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 16:11:28 by nfordoxc         ###   Luxembourg.lu     */
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
		ParserServerConfig					pc("./good_config/good_config_1.conf");
		EventMonitoring						em;
		ServerManager						sm(pc.getListTokens(), em);

		assert(sm.getNbServer() == 3);
		std::cout << "✅ [OK] Number of servers parsed correctly" << std::endl;

		Server* s1 = sm.getServer(8080);
		assert(s1 != NULL);
		assert(s1->getPort() == 8080);
		assert(s1->getName() == "localhost");
		assert(s1->getPath() == "./www/html");
		assert(s1->getIndex() == "index.html");
		assert(s1->getMaxClient() == 10);
		assert(s1->getMaxSizeBody() == 5 * 1024 * 1024);
		std::cout << "✅ [OK] Server 8080 config valid" << std::endl;

		Server* s2 = sm.getServer(443);
		assert(s2 != NULL);
		assert(s2->checkUri("/images"));
		assert(s2->checkUri("/downloads"));
		assert(s2->checkMethod("/images", "GET"));
		assert(!s2->checkMethod("/images", "POST"));
		std::cout << "✅ [OK] Server 443 location/method valid" << std::endl;

		Server* s3 = sm.getServer(21);
		assert(s3 != NULL);
		assert(s3->checkUri("/deleteable"));
		assert(s3->checkMethod("/deleteable", "DELETE"));
		assert(s3->checkMethod("/redirect", "GET"));
		std::cout << "✅ [OK] Server 21 config valid" << std::endl;

		assert(s1->getPathError(403) == "./errors/403.html");
		assert(s1->getPathError(404) == "./errors/404.html");
		assert(s1->getPathError(418) == "./errors/418.html");
		std::cout << "✅ [OK] Error page paths valid" << std::endl;
	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}