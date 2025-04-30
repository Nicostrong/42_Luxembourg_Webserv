/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:43 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/30 10:16:27 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"

int main()
{
	CGI_Handler cgi;
	std::cout << cgi.DoCGI("/usr/bin/python3", "simplewindow.py") << "\n";
	return 0;
}