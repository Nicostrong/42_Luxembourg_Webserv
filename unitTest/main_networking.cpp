/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/22 13:17:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server/Server.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/server/ServerManager.hpp"
#include "../includes/parser/ParserServerConfig.hpp"
#include "../includes/CGI.hpp"

int main()
{
	try
	{
		ParserServerConfig		pc("../config/webserver.conf");
		EventMonitoring			em;
		ServerManager			sm(pc.getAllTokens(), em);
		CGI cgi;
		
		cgi.launch();
		(void)sm;
		sm.startAll();
		//while (1)
			//em.updateEvents();
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