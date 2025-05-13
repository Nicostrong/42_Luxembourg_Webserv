/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:19:33 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 15:24:34 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ParserServerConfig.hpp"

int		main( int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test_parser \"path_to_config_file\"" << std::endl;
		return (1);
	}
	try
	{
		ParserServerConfig		pc(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}