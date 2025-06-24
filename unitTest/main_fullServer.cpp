/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fullServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:28:13 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/22 11:22:52 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "../includes/HandleConfig.hpp"
#include "../includes/server/ServerManager.hpp"
#include "../includes/parser/ParserServerConfig.hpp"

int	main( void )
{
	try
	{
		ParserServerConfig								pc("../config/webserv.conf");
		EventMonitoring									em;
		ServerManager									sm(pc.getAllTokens(), em);
		const std::set<Server*>							setServ = sm.getAllServers();
		std::set<Server*>::const_iterator				itServ = setServ.begin();
		Ip												ip("127.120.120.0");

		assert(sm.getNbServer() == 4);
		std::cout << "✅ [OK] Number of servers parsed correctly" << std::endl;
		for ( ; itServ != setServ.end(); ++itServ)
			std::cout << **itServ << std::endl;
		std::cout << "Test new method object IP" << std::endl;
		std::cout << *sm.getMatchingServer(ip, 2121, "toto") << std::endl;
		std::cout << "✅✅✅✅✅✅✅ [OK] ALL IS ALLRIGHT ✅✅✅✅✅✅✅" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}