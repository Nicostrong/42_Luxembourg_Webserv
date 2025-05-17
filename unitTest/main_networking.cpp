/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/17 11:56:42 by nicostrong       ###   Luxembourg.lu     */
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
		ParserServerConfig		pc("../config/webserver.conf");
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