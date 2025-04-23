/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:43 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 17:02:54 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"

int main()
{
	CGI_Handler cgi;
	cgi.DoCGI("/usr/bin/python3", "cgitest.py");
	cgi.DoCGI("/usr/bin/python3", "cgitest1.py");
	cgi.DoCGI("/usr/bin/python3", "cgitest2.py");
	cgi.DoCGI("/usr/bin/python3", "cgitest3.py");
	cgi.DoCGI("/usr/bin/python3", "cgitest4.py");
	cgi.DoCGI("/usr/bin/python3", "cgitest5.py");
	return 0;
}