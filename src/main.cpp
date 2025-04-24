/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:29:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/16 16:02:45 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		HandleConfig hc;
		hc.readConfigFile(argv[1]);
		hc.cleanMap();
		hc.getNicoMap();
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return (0);
}