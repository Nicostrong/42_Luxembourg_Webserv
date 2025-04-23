/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/23 14:25:40 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIHandler.hpp"
#include <cstdlib>

CGI_Handler::CGI_Handler()
{
	compilers["python"] = "/usr/bin/python";
}

CGI_Handler::~CGI_Handler()
{
	
}

CGI_Handler::CGI_Handler(CGI_Handler& copy)
{
	(void)copy;
}

CGI_Handler& CGI_Handler::operator=(CGI_Handler& copy)
{
	(void)copy;
	return *this;
}

bool CGI_Handler::DoCGI(const char *compiler, const char *script)
{
	pid_t c_pid = fork(); 
  
    if (c_pid == -1) { 
        //perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    else if (c_pid > 0) { 
        //  wait(nullptr); 
        std::cout << "printed from parent process " << getpid() 
             << "\n";
    } 
    else { 
        std::cout << "printed from child process " << getpid() 
             << "\n";
			 const char *cmd_list[3] = { compiler, script, NULL };
			 execve(compiler, (char * const *)cmd_list, NULL);
    } 
  
    return 0; 
}

std::map<std::string, std::string> CGI_Handler::getCompilers()
{
	return compilers;
}