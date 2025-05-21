/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/21 11:17:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server/Server.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/server/ServerManager.hpp"
#include "../includes/parser/ParserServerConfig.hpp"

int main()
{
	try
	{
		ParserServerConfig		pc("../config/webserv.conf");
		EventMonitoring			em;
		ServerManager			sm(pc.getAllTokens(), em);

		sm.startAll();
		while (1)
			em.updateEvents();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}		
	return (0);
}