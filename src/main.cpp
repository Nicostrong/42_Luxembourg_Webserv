/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:46:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server/Server.hpp"
#include "../includes/networking/Listener.hpp"
#include "../includes/server/ServerManager.hpp"
#include "../includes/events/EventMonitoring.hpp"
#include "../includes/networking/SocketManager.hpp"
#include "../includes/networking/ListenerManager.hpp"
#include "../includes/parser/ParserServerConfig.hpp"

bool	g_running = true;

void	handle_sigint( int signal )
{
	if (signal == SIGINT)
		g_running = false;
	return ;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		LOG_DEB("Usage: webserv [path to config file]");
		return (0);
	}
	
	signal(SIGINT, handle_sigint);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		std::string configPath = "./config/webserver.conf";

		if (argc == 2)
			configPath = argv[1];
		
		ParserServerConfig		pc(configPath);
		ServerManager			sm(pc.getAllTokens());
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
		LOG_ERROR(e.what());
		return (1);
	}
	return (0);
}
