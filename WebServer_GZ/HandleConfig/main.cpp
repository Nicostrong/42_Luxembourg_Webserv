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
	if (argc == 2)
	{
		HandleConfig hc(argv[1]);
	}
	else
	{
		std::cerr << "Usage: ./webserv <config_file>.\n";
	}
	return 0;
}