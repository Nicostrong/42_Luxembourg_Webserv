/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/02 13:06:31 by gzenner          ###   ########.fr       */
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

std::string HandleCGI::DoCGI(const char *cmd_list[3], EventMonitoring& em)
{
    Pipe send_data_to_cgi();
    Pipe receive_data_from_cgi();
    
    em.monitor(send_data_to_cgi.getIn(), POLLIN | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);

    em.monitor(receive_data_from_cgi.getOut(), POLLOUT | POLLHUP | POLLRDHUP,
			    EventData::CLIENT, *this);
    
    pid_t pid = fork(); 

    if (pid == -1) { 
        std::cerr << "fork failed\n"; 
        return "ERROR\n";
    } 
    else if (pid == 0) {
        dup2(send_data_to_cgi.getOut(), STDOUT_FILENO);
        dup2(receive_data_from_cgi.getIn(), STDIN_FILENO);
        send_data_to_cgi.closeIn();
        receive_data_from_cgi.closeOut();
        execve(cmd_list[0], (char * const *)cmd_list, environ);
        _exit(1);
    } 
    else {
        char buffer[1024];
        send_data_to_cgi.closeOut();
        receive_data_from_cgi.closeIn();
        ssize_t count;
        std::string output;
        while ((count = read(receive_data_from_cgi.getOut(), buffer, sizeof(buffer))) > 0) {
            output.append(buffer, count);
        }
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

void HandleCGI::onReadEvent(int fd, int type, EventMonitoring& em)
{   
    (void)fd;
    (void)type;
    (void)em;
    return ;
}
void HandleCGI::onWriteEvent(int fd, int type, EventMonitoring& em)
{
    (void)fd;
    (void)type;
    (void)em;
    return ;
}
void HandleCGI::onCloseEvent(int fd, int type, EventMonitoring& em)
{
    (void)fd;
    (void)type;
    (void)em;
    return ;
}