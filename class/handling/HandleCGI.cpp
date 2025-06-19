/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:06:44 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/19 15:26:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/HandleCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
******************************************************************************/

HandleCGI::HandleCGI(Socket& socket)
	:	_txBuffer(RESPONSE_BUFFER_SIZE), _rxBuffer(RX_SIZE), _aEnv(NULL),
		_aCmd(NULL) , _endWrite(false), _endRead(false)
{
	this->_socket = &socket;
	initEnvironMapNULL();
	completeMyEnv(socket);
	map_to_chartab();
	createCmdLst(socket);
	return ;
}

HandleCGI::~HandleCGI( void )
{
	if (this->_aEnv)
		delete[] this->_aEnv;
	if (this->_aCmd)
	{
		for (int i = 0; i < 4; ++i)
			free(this->_aCmd[i]);
		delete[] this->_aCmd;
	}
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
*	Initialize all element of the map for environnement value for execve
*/
void		HandleCGI::initEnvironMapNULL( void )
{
	this->_environmap["AUTH_TYPE"] = "";
	this->_environmap["CONTENT_LENGTH"] = "";
	this->_environmap["CONTENT_TYPE"] = "";
	this->_environmap["GATEWAY_INTERFACE"] = "";
	this->_environmap["PATH_INFO"] = "";
	this->_environmap["PATH_TRANSLATED"] = "";
	this->_environmap["QUERY_STRING"] = "";
	this->_environmap["REMOTE_ADDR"] = "";
	this->_environmap["REMOTE_HOST"] = "";
	this->_environmap["REMOTE_IDENT"] = "";
	this->_environmap["REMOTE_USER"] = "";
	this->_environmap["REQUEST_METHOD"] = "";
	this->_environmap["SCRIPT_NAME"] = "";
	this->_environmap["SERVER_NAME"] = "";
	this->_environmap["SERVER_PORT"] = "";
	this->_environmap["SERVER_PROTOCOL"] = "";
	this->_environmap["SERVER_SOFTWARE"] = "";
	return ;
}

/*
*	Get all value to complete the map of environnement variable
*/
void		HandleCGI::completeMyEnv( Socket& socket )
{
	std::ostringstream		oss;
	HttpRequest*			req = &socket.getReq();

	this->_environmap["AUTH_TYPE"] = "nfordoxc";
	this->_environmap["GATEWAY_INTERFACE"] = CGI_REVISION;

	oss << req->getContentLength();
	this->_environmap["CONTENT_LENGTH"] = oss.str();
	oss.str("");
	oss.clear();

	this->_environmap["PATH_INFO"] = req->getPathInfo();
	this->_environmap["PATH_TRANSLATED"] = req->getPathTranslated();
	this->_environmap["QUERY_STRING"] = req->getQueryParams();
	this->_environmap["REMOTE_ADDR"] = req->getRemotIp();

	oss << socket.getSocket();
	this->_environmap["REMOTE_IDENT"] = oss.str();
	oss.str("");
	oss.clear();

	this->_environmap["REQUEST_METHOD"] = req->getMethod();
	this->_environmap["SCRIPT_NAME"] = req->getCgiScript();
	if (req->getServer() && !req->getServer()->getHost().empty())
		this->_environmap["SERVER_NAME"] = req->getServer()->getHost().front();
	
	oss << *req->getServer()->getPortList().begin();
	this->_environmap["SERVER_PORT"] = oss.str();
	oss.str("");
	oss.clear();

	this->_environmap["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_environmap["SERVER_SOFTWARE"] = SERVER_VER;

	/*std::cout << "[DEBUG CGI]\t\t========== PRINTING ===========" << std::endl;
	std::map<std::string,std::string>::const_iterator	itMap;

	for(itMap = this->_environmap.begin(); itMap != this->_environmap.end(); ++itMap)
		std::cout << itMap->first << "\t=>\t" << itMap->second << std::endl;
	
	std::cout << *req << std::endl;*/
	return ;
}

//Function goes into CGI - splits the string into map values
void		HandleCGI::string_to_map( void )
{
	std::string		tmp = this->_data;

	while (tmp.find("&") != std::string::npos)
	{
		std::string		snippet = tmp.substr(0, tmp.find("&"));
		std::string		key = snippet.substr(0, snippet.find("="));
		std::string		value = snippet.substr(snippet.find("=") + 1);

		tmp = tmp.substr(tmp.find("&") + 1);
		this->_mData[key] = value;
	}
	std::string		snippet = tmp.substr(0, tmp.find("&"));
	std::string		key = snippet.substr(0, snippet.find("="));
	std::string		value = snippet.substr(snippet.find("=") + 1);

	this->_mData[key] = value;
	return ;
}

void		HandleCGI::map_to_chartab()
{
	std::map<std::string, std::string>::iterator		it;
	size_t												i = 0;

	this->_aEnv = new char*[this->_mData.size() * 4 + 1];
	for (it = this->_mData.begin(); it != this->_mData.end(); ++it)
	{
		this->_aEnv[i++] = strdup(it->first.c_str());
		this->_aEnv[i++] = strdup(";");
		this->_aEnv[i++] = strdup(it->second.c_str());
		this->_aEnv[i++] = strdup(";");
	}
	this->_aEnv[i] = NULL;
	
	return ;
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

	this->_aCmd = new char*[4];

	this->_aCmd[0] = strdup(path.c_str());
	this->_aCmd[1] = strdup(script.c_str());
	this->_aCmd[2] = strdup(query.c_str());
	this->_aCmd[3] = NULL;
	
	return;
}

/*******************************************************************************
 *								METHOD										   *
******************************************************************************/

char**		HandleCGI::getCmd( void )
{
	return (this->_aCmd);
}

char**		HandleCGI::getEnv( void )
{
	return (this->_aEnv);
}

/*
 *	Pipe.getIn()	=>	WRITING PIPE 1
 *	Pipe.getOut()	=>	READING PIPE 0
 */
void		HandleCGI::DoCGI( Socket& socket )
{
	pid_t				pid;
	EventMonitoring		em = socket.getEM();
	char**				cmd = getCmd();
	
	em.monitor(this->_dataToCGI.getIn(), POLLIN | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
				
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "fork failed\n"; 
		return ;
	}
	else if (pid == 0)
	{
		this->_dataToCGI.closeIn();
		this->_dataFromCGI.closeOut();
		if (dup2(this->_dataToCGI.getOut(), STDIN_FILENO) == -1)
			std::runtime_error("[ERROR] dup2 IN");
		this->_dataToCGI.closeOut();
		if (dup2(this->_dataFromCGI.getIn(), STDOUT_FILENO) == -1)
			std::runtime_error("[ERROR] dup2 IN");
		this->_dataFromCGI.closeIn();
		execve(cmd[0], cmd, this->getEnv());
		std::cerr << "ERROR execve\n";
		exit(EXIT_FAILURE);	//!\\ LEAKS
	} 
	else
	{
		this->_dataToCGI.closeOut();
		this->_dataFromCGI.closeIn();
		onWriteEvent(this->_dataToCGI.getIn(), 0, em);
		onReadEvent(this->_dataFromCGI.getOut(), 0, em);
		//	le parent doit ecrire le body dans le pipe
		//	le parent doit lire l autre pipe
	}
	
	return ;
}
