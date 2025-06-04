/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 15:23:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server/Server.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/server/ServerManager.hpp"
#include "../includes/parser/ParserServerConfig.hpp"
#include "../includes/CGI.hpp"
#include "../includes/SocketManager.hpp"
#include "../includes/ServerListener.hpp"

bool	g_running = true;

void	handle_sigint( int signal )
{
	if (signal == SIGINT)
		g_running = false;
}

int main()
{
	signal(SIGINT, handle_sigint);
	try
	{
		ParserServerConfig		pc("../config/webserv.conf");
		EventMonitoring			em;
		SocketManager			sockm;

		ServerManager			sm(pc.getAllTokens());
		ServerListener			sl(std::pair<Ip, size_t>(Ip("0.0.0.0"), 8080), sockm, sm);

		sl.listenSocket(em);

		//CGI cgi;
		
		//cgi.launch();
		//sm.startAll();
		while (g_running)
			em.updateEvents();
	}
	catch (const CGI::ForkClean& e)
	{
		LOG_DEB("Fork exit");
		return (1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}		
	return (0);
}