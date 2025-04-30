/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:29:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/30 08:32:43 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.hpp"
#include "../includes/HandleConfig.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		HandleConfig hc;
		hc.saveRawConfig(argv[1]);
		hc.genTmpMap();
		hc.genWebconfMap();
		hc.getwebconfMap();
//		hc.printwebconfMap();
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return (0);
}