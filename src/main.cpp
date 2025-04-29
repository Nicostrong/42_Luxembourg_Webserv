/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:29:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/29 13:10:14 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.hpp"
#include "../includes/HandleConfig.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		HandleConfig hc;
		hc.readConfigFile(argv[1]);
		hc.cleanMap();
		hc.getwebconfMap();
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return (0);
}