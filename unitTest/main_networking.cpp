/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/16 10:54:30 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parser/ParserServerConfig.hpp"
#include "./../includes/server/ServerManager.hpp"
#include "./../includes/server/Server.hpp"
#include "./../includes/events/EventMonitoring.hpp"
#include "./../includes/networking/SocketManager.hpp"
#include "./../includes/networking/Listener.hpp"
#include "./../includes/networking/ListenerManager.hpp"
#include "./../includes/handling/CGI.hpp"

bool	g_running = true;

void	handle_sigint( int signal )
{
	if (signal == SIGINT)
		g_running = false;
	return ;
}

int main()
{
	signal(SIGINT, handle_sigint);
	signal(SIGSEGV, handle_sigint);
	try
	{
		ParserServerConfig		pc("../config/webserv.conf");
		ServerManager			sm(pc.getAllTokens());
		EventMonitoring			em;
		SocketManager			sockm;
		ListenerManager			lm(sm, sockm, em);
		
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
		return (1);
	}
	return (0);
}
