/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:30:19 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 13:55:23 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleConfig.hpp"

int main(int argc, char **argv)
{
    (void)argv;
	if (argc == 2)
	{
		HandleConfig hc;
        hc.saveRawConfig(argv[1]);
        hc.genTmpMap();
        hc.genWebconfMap();
        hc.printwebconfMap();
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return 0;
}