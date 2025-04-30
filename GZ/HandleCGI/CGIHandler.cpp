/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/30 16:54:57 by gzenner          ###   ########.fr       */
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

HandleCGI::HandleCGI()
{
}

HandleCGI::~HandleCGI()
{
	
}

HandleCGI::HandleCGI(HandleCGI& copy)
{
	(void)copy;
}

HandleCGI& HandleCGI::operator=(HandleCGI& copy)
{
	(void)copy;
	return *this;
}

std::string HandleCGI::DoCGI(const char *cmd_list[3])
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "pipe failed\n";
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

//"/usr/bin/python3", "update_register_newsletter.py"

void HandleCGI::UpdateNewsLetter(const char *compiler, const char *script)
{
	const char *cmd_list[] = { compiler, script, "abc", NULL};
	std::cout << DoCGI(cmd_list);
}

void HandleCGI::UpdateShowData(const char *compiler, const char *script)
{
	const char *cmd_list[] = { compiler, script, "abc", "abc", "abc", "abc", NULL};
	std::cout << DoCGI(cmd_list);
}