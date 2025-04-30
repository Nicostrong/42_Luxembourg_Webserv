/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:07:43 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/30 16:57:39 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"

int main()
{
	HandleCGI cgi;
	
	cgi.UpdateNewsLetter("/usr/bin/python3", "update_register_newsletter.py");
	cgi.UpdateShowData("/usr/bin/python3", "update_showdata.py");
	return (0);
}