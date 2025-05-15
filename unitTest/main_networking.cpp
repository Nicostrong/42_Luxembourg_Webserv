/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/15 16:46:52 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerManager.hpp"
#include "../includes/Server.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/ParserServerConfig.hpp"

int main()
{
	ParserServerConfig	pc("../config/webserver.conf");
	EventMonitoring em;
	ServerManager	sm(pc.getListTokens(), em);

	sm.startAll();
	while (1)
		em.updateEvents();
	return (0);
}