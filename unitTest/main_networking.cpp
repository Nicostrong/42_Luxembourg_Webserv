/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 22:34:26 by fdehan           ###   ########.fr       */
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

	std::vector<ServerListener*>	slVector;
	std::vector<ServerListener*>::const_iterator it1;
	try
	{
		ParserServerConfig		pc("../config/webserv.conf");
		EventMonitoring			em;
		SocketManager			sockm;

		ServerManager			sm(pc.getAllTokens());
		
		const std::set<std::pair<Ip, size_t> > endpoints = sm.getSocketSet();
		std::set<std::pair<Ip, size_t> >::const_iterator it;
		
		slVector.reserve(endpoints.size());
		for (it = endpoints.begin(); it != endpoints.end(); ++it)
		{
			ServerListener* sl = new ServerListener(
				Endpoint(it->first, it->second), sockm, sm);
			
			if (sl)
				slVector.push_back(sl);
			sl->listenSocket(em);
		}
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
	
	for (it1 = slVector.begin(); it1 != slVector.end(); ++it1)
		delete *it1;
	
	return (0);
}