/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:30:40 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/24 15:18:34 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_Handler_HPP
#define CGI_Handler_HPP

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>

class CGI_Handler
{
	public:
		CGI_Handler();
		CGI_Handler(CGI_Handler& copy);
		CGI_Handler& operator=(CGI_Handler& copy);
		~CGI_Handler();
		std::string DoCGI(const char *compiler, const char *script);
};

#endif