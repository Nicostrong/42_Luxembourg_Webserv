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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

extern char **environ;

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

std::string CGI_Handler::DoCGI(const char *compiler, const char *script)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "pipe failed\n";
        return "ERROR\n";
    }

    if(!compiler || !script)
    {
        std::cerr << "Error: Compiler not in List.\n";
        return "ERROR\n";
    }

    pid_t pid = fork(); 

    if (pid == -1) { 
        std::cerr << "fork failed\n"; 
        return "ERROR\n";
    } 
    else if (pid == 0) { 
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        const char *cmd_list[] = { compiler, script, NULL };
        execve(cmd_list[0], (char * const *)cmd_list, environ);
        _exit(1);
    } 
    else {
        close(pipefd[1]);
        char buffer[1024];
        ssize_t count;
        std::string output = "";
        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, count);
        }
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
        return output;
    }
    return "ERROR\n"; 
}
