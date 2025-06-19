/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/19 15:09:20 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/HandleCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
******************************************************************************/

HandleCGI::HandleCGI(Socket& socket) : newenviron(NULL), lCmd(NULL)
{
	initEnvironMapNULL();
	completeEnvironMap(socket);
	map_to_chartab();
	createCmdLst(socket);
}

HandleCGI::~HandleCGI( void )
{
	if (this->newenviron)
		delete[] newenviron;
	if (lCmd)
	{
		for (int i = 0; i < 4; ++i)
			free(lCmd[i]);
		delete[] lCmd;
	}
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
******************************************************************************/

/*
*	Initialize all element of the map for environnement value for execve
*/
void	HandleCGI::initEnvironMapNULL()
{
	environmap["AUTH_TYPE"] = "";
	environmap["CONTENT_LENGTH"] = "";
	environmap["CONTENT_TYPE"] = "";
	environmap["GATEWAY_INTERFACE"] = "";
	environmap["PATH_INFO"] = "";
	environmap["PATH_TRANSLATED"] = "";
	environmap["QUERY_STRING"] = "";
	environmap["REMOTE_ADDR"] = "";
	environmap["REMOTE_HOST"] = "";
	environmap["REMOTE_IDENT"] = "";
	environmap["REMOTE_USER"] = "";
	environmap["REQUEST_METHOD"] = "";
	environmap["SCRIPT_NAME"] = "";
	environmap["SERVER_NAME"] = "";
	environmap["SERVER_PORT"] = "";
	environmap["SERVER_PROTOCOL"] = "";
	environmap["SERVER_SOFTWARE"] = "";
}

/*
*	Get all value to complete the map of environnement variable
*/
void	HandleCGI::completeEnvironMap( Socket& socket )
{
	std::ostringstream		oss;
	HttpRequest*			req = &socket.getReq();

	environmap["AUTH_TYPE"] = "nfordoxc";
	environmap["GATEWAY_INTERFACE"] = CGI_REVISION;

	oss << req->getContentLength();
	this->environmap["CONTENT_LENGTH"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["PATH_INFO"] = req->getPathInfo();
	environmap["PATH_TRANSLATED"] = req->getPathTranslated();
	environmap["QUERY_STRING"] = req->getQueryParams();
	environmap["REMOTE_ADDR"] = req->getRemotIp();

	oss << socket.getSocket();
	environmap["REMOTE_IDENT"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["REQUEST_METHOD"] = req->getMethod();
	environmap["SCRIPT_NAME"] = req->getCgiScript();
	if (req->getServer() && !req->getServer()->getHost().empty())
		this->environmap["SERVER_NAME"] = req->getServer()->getHost().front();
	
	oss << *req->getServer()->getPortList().begin();
	this->environmap["SERVER_PORT"] = oss.str();
	oss.str("");
	oss.clear();

	environmap["SERVER_PROTOCOL"] = "HTTP/1.1";
	environmap["SERVER_SOFTWARE"] = SERVER_VER;

	/*std::cout << "[DEBUG CGI]\t\t========== PRINTING ===========" << std::endl;
	std::map<std::string,std::string>::const_iterator	itMap;

	for(itMap = environmap.begin(); itMap != environmap.end(); ++itMap)
		std::cout << itMap->first << "\t=>\t" << itMap->second << std::endl;
	
	std::cout << *req << std::endl;*/
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

char * const*	HandleCGI::map_to_chartab()
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

/*
*	il faut creer un array pour le exeve du fork
*/
void		HandleCGI::createCmdLst( Socket& socket )
{
	std::string		path = socket.getReq().getCgiPath();
	std::string		script = socket.getReq().getPathTranslated();
	std::string		query = socket.getReq().getQueryParams();

	std::cout	<< "[DEBUUUUG]" << std::endl
				<< "PATH: " << path << std::endl
				<< "SCRIPT: " << script << std::endl
				<< "QUERY: " << query << std::endl;

	this->lCmd = new char*[4];

	lCmd[0] = strdup(path.c_str());
	lCmd[1] = strdup(script.c_str());
	lCmd[2] = strdup(query.c_str());
	lCmd[3] = NULL;
	
	return;
}



/*******************************************************************************
 *							SERVER EVENTS									   *
******************************************************************************/

void	HandleCGI::onReadEvent(int fd, EventMonitoring& em)
{
	(void)fd;
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

void	HandleCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	(void)fd;
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

void	HandleCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	(void)fd;
	(void)em;
	
	em.unmonitor(fd);
	close(fd);
	input.clear();
	output.clear();

	return ;
}

void HandleCGI::onTickEvent( int fd, EventMonitoring& em )
{
	(void)fd;
	(void)em;
}

/*******************************************************************************
 *								METHOD										   *
******************************************************************************/

char**		HandleCGI::getLCmd( void )
{
	return (this->lCmd);
}

char**		HandleCGI::getNewEnv( void )
{
	return (this->newenviron);
}

void	HandleCGI::DoCGI( Socket& socket )
{
	Pipe				send_data_to_cgi;
	Pipe				receive_data_from_cgi;
	pid_t				pid;
	EventMonitoring		em = socket.getEM();
	char**				cmd = getLCmd();
	char**				env = getNewEnv();
	
	em.monitor(send_data_to_cgi.getIn(), POLLIN | POLLHUP | POLLRDHUP,
				*this);

	em.monitor(receive_data_from_cgi.getOut(), POLLOUT | POLLHUP | POLLRDHUP,
				*this);
	
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "fork failed\n"; 
		return ;
	}
	else if (pid == 0)
	{
		dup2(send_data_to_cgi.getOut(), STDOUT_FILENO);
		dup2(receive_data_from_cgi.getIn(), STDIN_FILENO);
		send_data_to_cgi.closeIn();
		receive_data_from_cgi.closeOut();
		execve(cmd[0], cmd, env);
		_exit(1);
	} 
	else
	{
		send_data_to_cgi.closeOut();
		receive_data_from_cgi.closeIn();
	}
	return ;
}

//"/usr/bin/python3", "update_register_newsletter.py"

void	HandleCGI::UpdateNewsLetter(const char *compiler, const char *script, const char *newvalue)
{
	(void)compiler;
	(void)script;
	(void)newvalue;
	//const char *cmd_list[] = { compiler, script, newvalue, NULL};
	//std::cout << DoCGI(cmd_list);
}

void	HandleCGI::UpdateShowData(const char *compiler, const char *script, const char *newvalue)
{
	(void)compiler;
	(void)script;
	(void)newvalue;
	//const char *cmd_list[] = { compiler, script, newvalue, newvalue, newvalue, newvalue, NULL};
	//std::cout << DoCGI(cmd_list);
}