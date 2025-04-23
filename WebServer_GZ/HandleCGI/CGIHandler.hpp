/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:30:40 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 16:20:00 by gzenner          ###   ########.fr       */
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
	private:
		std::map<std::string, std::string> compilers;
	public:
		CGI_Handler();
		CGI_Handler(CGI_Handler& copy);
		CGI_Handler& operator=(CGI_Handler& copy);
		~CGI_Handler();
		std::map<std::string, std::string> getCompilers();
		bool DoCGI(const char *compiler, const char *script);
};

#endif