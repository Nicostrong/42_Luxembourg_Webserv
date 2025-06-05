/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/05 11:17:16 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/HandleCGI.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

extern char **environ;

/*
We need to add

AUTH_TYPE: Type of authentication used (if any).

CONTENT_LENGTH: Length of the request body (for POST requests).

CONTENT_TYPE: MIME type of the request body (for POST requests).

GATEWAY_INTERFACE: Version of CGI being used (e.g., "CGI/1.1").

PATH_INFO: Extra path information after the script name.

PATH_TRANSLATED: Translated version of PATH_INFO (filesystem path).

QUERY_STRING: Data from the URL after the "?" (for GET requests).

REMOTE_ADDR: IP address of the client.

REMOTE_HOST: Hostname of the client (if available).

REMOTE_IDENT: Remote user name (if available, rarely used).

REMOTE_USER: Authenticated user name (if applicable).

REQUEST_METHOD: HTTP method (GET, POST, etc.).

SCRIPT_NAME: Path to the script being executed.

SERVER_NAME: Server's hostname or IP.

SERVER_PORT: Port number the server is listening on.

SERVER_PROTOCOL: Protocol and version (e.g., "HTTP/1.1").

SERVER_SOFTWARE: Name and version of the server software.

to environ

So we need to get those values from from the Parsing to here and add them to environ
Most of these values will be empty/NULL
I think we have to add a function to the Parsing that initiates all these to NULL and then replaces them with the real values if found.
*/

HandleCGI::HandleCGI()
{
    
}

HandleCGI::HandleCGI(std::string& _data)
{
    this->data = _data;
    string_to_map();
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
	return (*this);
}

void HandleCGI::DoCGI(const char *cmd_list[3], EventMonitoring& em)
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
        return ;
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
        //char buffer[1024];
        send_data_to_cgi.closeOut();
        receive_data_from_cgi.closeIn();
        /*ssize_t count;
        while ((count = read(receive_data_from_cgi.getOut(), buffer, sizeof(buffer))) > 0) {
            output.append(buffer, count);
        }*/
    }
    return ;
}

//"/usr/bin/python3", "update_register_newsletter.py"

void HandleCGI::UpdateNewsLetter(const char *compiler, const char *script, const char *newvalue)
{
	const char *cmd_list[] = { compiler, script, newvalue, NULL};
	std::cout << DoCGI(cmd_list);
}

void HandleCGI::UpdateShowData(const char *compiler, const char *script, const char *newvalue)
{
	const char *cmd_list[] = { compiler, script, newvalue, newvalue, newvalue, newvalue, NULL};
	std::cout << DoCGI(cmd_list);
}

void HandleCGI::onReadEvent(int fd, int type, EventMonitoring& em)
{
    (void)fd;
    (void)type;
    (void)em;

    char buffer[1024];
    ssize_t count;

    count = read(fd, buffer, sizeof(buffer));
    if (count > 0)
    {
        this->output.append(buffer, count);
    }
    else if (count == 0)
    {
        em.unmonitor(fd);
        close(fd);
    }
    else
    {
        std::cerr << "Error reading from CGI pipe\n";
        em.unmonitor(fd);
        close(fd);
    }
    return ;
}
void HandleCGI::onWriteEvent(int fd, int type, EventMonitoring& em)
{
    (void)fd;
    (void)type;
    (void)em;

    if (input.size() > input_sent) {
        ssize_t written = write(fd, input.c_str() + input_sent, input.size() - input_sent);
        if (written > 0) {
            input_sent += written;
            if (input_sent == input.size()) {
                em.unmonitor(fd);
                close(fd);
            }
        } else if (written < 0) {
            std::cerr << "Error writing to CGI pipe\n";
            em.unmonitor(fd);
            close(fd);
        }
    } else {
        em.unmonitor(fd);
        close(fd);
    }    
    return ;
}
void HandleCGI::onCloseEvent(int fd, int type, EventMonitoring& em)
{
    (void)fd;
    (void)type;
    (void)em;
    
    em.unmonitor(fd);
    close(fd);
    input.clear();
    output.clear();

    return ;
}

//Function goes into CGI - splits the string into map values
void HandleCGI::string_to_map()
{
    std::string tmp = data;
    while(tmp.find("&") != std::string::npos)
    {
        std::string snippet = tmp.substr(0, tmp.find("&"));
        tmp = tmp.substr(tmp.find("&") + 1);
        std::string key = snippet.substr(0, snippet.find("="));
        std::string value = snippet.substr(snippet.find("=") + 1);
        datamap[key] = value;
    }
    std::string snippet = tmp.substr(0, tmp.find("&"));
    std::string key = snippet.substr(0, snippet.find("="));
    std::string value = snippet.substr(snippet.find("=") + 1);
    datamap[key] = value;
}