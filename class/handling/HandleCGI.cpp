/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:05:29 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/06 09:12:05 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/HandleCGI.hpp"

HandleCGI::HandleCGI()
{
	
}

HandleCGI::HandleCGI(*cmd_list[3], EventMonitoring& em, std::string& data, Socket& socket)
{
	this->data = data;
	initEnvironMapNULL();
    completeEnvironMap(socket);
	map_to_chartab();
	DoCGI(*cmd_list[3], em);
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
	Pipe send_data_to_cgi;
	Pipe receive_data_from_cgi;
	
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
		execve(cmd_list[0], (char * const *)cmd_list, newenviron);
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
	//std::cout << DoCGI(cmd_list);
}

void HandleCGI::UpdateShowData(const char *compiler, const char *script, const char *newvalue)
{
	const char *cmd_list[] = { compiler, script, newvalue, newvalue, newvalue, newvalue, NULL};
	//std::cout << DoCGI(cmd_list);
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
	while (tmp.find("&") != std::string::npos)
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

char * const* HandleCGI::map_to_chartab()
{
	size_t  i;
	
	i = 0;
	newenviron = new char*[datamap.size() * 4 + 1];
	for (std::map<std::string, std::string>::iterator it = datamap.begin(); it != datamap.end(); ++it)
	{
		newenviron[i++] = strdup(it->first.c_str());
		newenviron[i++] = strdup(";");
		newenviron[i++] = strdup(it->second.c_str());
		newenviron[i++] = strdup(";");
	}
	newenviron[i] = NULL;
	return (newenviron);
}

void HandleCGI::initEnvironMapNULL()
{
	environmap["AUTH_TYPE"] = "NULL";
	environmap["CONTENT_LENGTH"] = "NULL";
	environmap["CONTENT_TYPE"] = "NULL";
	environmap["GATEWAY_INTERFACE"] = "NULL";
	environmap["PATH_INFO"] = "NULL";
	environmap["PATH_TRANSLATED"] = "NULL";
	environmap["QUERY_STRING"] = "NULL";
	environmap["REMOTE_ADDR"] = "NULL";
	environmap["REMOTE_HOST"] = "NULL";
	environmap["REMOTE_IDENT"] = "NULL";
	environmap["REMOTE_USER"] = "NULL";
	environmap["SCRIPT_NAME"] = "NULL";
	environmap["SERVER_NAME"] = "NULL";
	environmap["SERVER_PORT"] = "NULL";
	environmap["SERVER_PROTOCOL"] = "NULL";
	environmap["SERVER_SOFTWARE"] = "NULL";
}

void		HandleCGI::completeEnvironMap( Socket& socket )
{
	//	environmap["AUTH_TYPE"] 			=>	NO
	//	environmap["CONTENT_LENGTH"] 		=>	YES
	//	environmap["CONTENT_TYPE"] 			=>	PERHAPS
	//	environmap["GATEWAY_INTERFACE"] 	=>	NO
	//	environmap["PATH_INFO"] 			=>	YES
	//	environmap["PATH_TRANSLATED"] 		=>	YES
	//	environmap["QUERY_STRING"] 			=>	YES
	//	environmap["REMOTE_ADDR"] 			=>	YES
	//	environmap["REMOTE_HOST"] 			=>	NO
	//	environmap["REMOTE_IDENT"] 			=>	YES	(fd of socket)
	//	environmap["REMOTE_USER"] 			=>	NO
	//	environmap["SCRIPT_NAME"] 			=>	YES
	//	environmap["SERVER_NAME"] 			=>	YES
	//	environmap["SERVER_PORT"] 			=>	YES
	//	environmap["SERVER_PROTOCOL"] 		=>	YES
	//	environmap["SERVER_SOFTWARE"] 		=>	NO
	std::ostringstream		oss;

	oss << socket.getReq().getContentLength();
	this->environmap["CONTENT_LENGTH"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["PATH_INFO"] = socket.getReq().getPathInfo();
	environmap["PATH_TRANSLATED"] = socket.getReq().getPathTranslated();
	environmap["QUERY_STRING"] = socket.getReq().getQueryParams();

	oss << socket.getReq().getRemotIp();
	environmap["REMOTE_ADDR"] = oss.str();
	oss.str("");
	oss.clear();

	oss << socket.getSocket();
	environmap["REMOTE_IDENT"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["SCRIPT_NAME"] = socket.getReq().getCgiScript();
	if (!socket.getReq().getServer()->getHost().empty())
		this->environmap["SERVER_NAME"] = socket.getReq().getServer()->getHost().front();
	
	oss << *socket.getReq().getServer()->getPortList().begin();
	this->environmap["SERVER_PORT"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["SERVER_PROTOCOL"] = "HTTP/1.1";
	return ;
}

char * const* HandleCGI::map_to_chartab()
{
    size_t  i;
    
    i = 0;
    newenviron = new char*[datamap.size() * 4 + 1];
    for (std::map<std::string, std::string>::iterator it = datamap.begin(); it != datamap.end(); ++it)
    {
        newenviron[i++] = strdup(it->first.c_str());
        newenviron[i++] = strdup(";");
        newenviron[i++] = strdup(it->second.c_str());
        newenviron[i++] = strdup(";");
    }
    newenviron[i] = NULL;
    return (newenviron);
}