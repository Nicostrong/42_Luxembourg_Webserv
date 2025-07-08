/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 13:54:36 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parser/ParserServerConfig.hpp"
#include "./../includes/server/ServerManager.hpp"
#include "./../includes/server/Server.hpp"
#include "./../includes/events/EventMonitoring.hpp"
#include "./../includes/networking/SocketManager.hpp"
#include "./../includes/networking/Listener.hpp"
#include "./../includes/networking/ListenerManager.hpp"

bool	g_running = true;

void	handle_sigint( int signal )
{
	if (signal == SIGINT)
		g_running = false;
	return ;
}

int main(int argc, char** argv)
{
	signal(SIGINT, handle_sigint);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		std::string configPath = "../config/webserv.conf";

		if (argc >= 2)
			configPath = argv[1];
		
		ParserServerConfig		pc(configPath);
		ServerManager			sm(pc.getAllTokens());
		const std::set<Server*>	lstServ = sm.getAllServers();
		/*std::set<Server*>::const_iterator	itServ;

		for (itServ = lstServ.begin(); itServ != lstServ.end(); ++itServ)
			std::cout << **itServ << std::endl;
		*/

		EventMonitoring			em;
		SocketManager			sockm;
		ListenerManager			lm(sm, sockm, em);
		
		while (g_running)
			em.updateEvents();
	}
	catch(const EventMonitoring::EPollCatchBypass& e)
	{
		return (1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
