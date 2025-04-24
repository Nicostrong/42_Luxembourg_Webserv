/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:43 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/24 15:42:41 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"

int main()
{
	CGI_Handler cgi;
	std::cout << cgi.DoCGI("/usr/bin/python3", "cgitest.py") << "\n";
	return 0;
}