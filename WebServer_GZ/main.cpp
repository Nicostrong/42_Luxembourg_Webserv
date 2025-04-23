/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:30:19 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 10:42:17 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleConfig.hpp"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		HandleConfig hc;
		hc.readConfigFile(argv[1]);
		hc.cleanMap();
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return 0;
}