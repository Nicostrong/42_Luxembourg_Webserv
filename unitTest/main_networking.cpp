/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_networking.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:18:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/06 20:53:55 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/EventMonitoring.hpp"
#include "../includes/Nico.hpp"

int main()
{
	ParserServerConfig	pc("../config/webserver.conf");
	EventMonitoring em;
	Server s(pc.getServer(2), em);
	s.start();
	return (0);
}