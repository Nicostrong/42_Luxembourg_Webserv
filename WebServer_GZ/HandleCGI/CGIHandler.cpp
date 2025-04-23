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
#include <sys/types.h>
#include <sys/wait.h>

CGI_Handler::CGI_Handler()
{
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
	if(!compiler || !script)
	{
		std::cerr << "Error: Compiler not in List.\n";
		return 1;
	}
	pid_t c_pid = fork(); 
  
    if (c_pid == -1) { 
        std::cerr << "fork\n"; 
        exit(EXIT_FAILURE); 
    } 
    else if (c_pid == 0) { 
        std::cout << "printed from child process " << getpid() 
             << "\n";
			 try
			 {
				const char *cmd_list[] = { compiler, script, NULL };
			 	execve(cmd_list[0], (char * const *)cmd_list, NULL);
			 } catch(std::exception &e)
			 {
				std::cout << e.what();
			 }
    } 
	else{
		int status;
		waitpid(c_pid, &status, 0);
		std::cout << "Child finished. Parent resumes work.\n";
		if (WIFEXITED(status)) {
				std::cout << "Child exited with status: " << WEXITSTATUS(status) << "\n";
			}
    }
  
    return 0; 
}
