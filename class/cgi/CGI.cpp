/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:09:40 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 15:18:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/CGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

CGI::CGI( Socket& socket )
	: _byteRead(0), _byteSend(0), _params(NULL), _aEnv(NULL), _toCGI(), 
	_fromCGI(), _txBuffer(BUFF_SIZE), _rxBuffer(BUFF_SIZE), _socket(&socket),
	_pid(-1), _exitCode(0), _isCloseEvent(false), _isReadEvent(false),
	_isTransferFinished(false), _isExited(false)
{
	socket.getHandler().setState(HttpHandling::CGI_SENDING);
	Fd::setNonBlocking(getPipeToCGI().getIn());
	Fd::setNonBlocking(getPipeFromCGI().getOut());
	this->_binaryExec = this->_socket->getReq().getCgiPath();
	this->_scriptPath = this->_socket->getReq().getPathTranslated();
	this->_query = this->_socket->getReq().getQueryParams();
	initMap();
	setMap();
	setEnv();
	setParams();
	checkCGI();
	LOG_DEB(*this);
	return ;
}

CGI::~CGI( void )
{
	int		i = -1;
	int		status = 0;

	if (this->_pid > 0 && waitpid(this->_pid, &status, WNOHANG) == 0)
		kill(this->_pid, SIGKILL);
	if (this->_params)
	{
		while (++i < 4)
		{
			if (this->_params[i])
				free(this->_params[i]);
			this->_params[i] = NULL;
		}
		delete[] this->_params;
		this->_params = NULL;
	}
	i = -1;
	if (this->_aEnv)
	{
		while (this->_aEnv[++i])
		{
			free(this->_aEnv[i]);
			this->_aEnv[i] = NULL;
		}
		delete[] this->_aEnv;
		this->_aEnv = NULL;
	}
	this->_socket->getEM().unmonitor(getPipeToCGI().getIn());
	this->_socket->getEM().unmonitor(getPipeFromCGI().getOut());
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
*	initialise all key environnement map with empty string value
*/
void		CGI::initMap( void )
{
	this->_mEnv["REDIRECT_STATUS"] = "";
	this->_mEnv["SCRIPT_FILENAME"] = "";
	this->_mEnv["DOCUMENT_ROOT"] = "";
	this->_mEnv["AUTH_TYPE"] = "";
	this->_mEnv["CONTENT_LENGTH"] = "";
	this->_mEnv["CONTENT_TYPE"] = "";
	this->_mEnv["GATEWAY_INTERFACE"] = "";
	this->_mEnv["PATH_INFO"] = "";
	this->_mEnv["PATH_TRANSLATED"] = "";
	this->_mEnv["QUERY_STRING"] = "";
	this->_mEnv["REMOTE_ADDR"] = "";
	this->_mEnv["REMOTE_HOST"] = "";
	this->_mEnv["REMOTE_IDENT"] = "";
	this->_mEnv["REMOTE_USER"] = "";
	this->_mEnv["REQUEST_METHOD"] = "";
	this->_mEnv["SCRIPT_NAME"] = "";
	this->_mEnv["SERVER_NAME"] = "";
	this->_mEnv["SERVER_PORT"] = "";
	this->_mEnv["SERVER_PROTOCOL"] = "";
	this->_mEnv["SERVER_SOFTWARE"] = "";
	this->_mEnv["REDIRECT_STATUS"] = "200";

	return ;
}

/*
 *	normalize the path to remove the "/../"
 */
std::string		CGI::normalizePath( const std::string& path )
{
	std::vector<std::string>		parts;
	std::stringstream				ss(path);
	std::string						part;
	bool							isAbsolute = (!path.empty() && path[0] == '/');

	while (std::getline(ss, part, '/'))
	{
		if (part.empty() || part == ".")
			continue;
		else if (part == "..")
		{
			if (!parts.empty() && parts.back() != "..")
				parts.pop_back();
			else if (!isAbsolute)
				parts.push_back(part);
		}
		else
			parts.push_back(part);
	}

	std::string		result;

	for (size_t i = 0; i < parts.size(); ++i)
	{
		if (i > 0 || isAbsolute)
			result += "/";
		result += parts[i];
	}
	if (result.empty())
		result = ".";
	return (result);
}

/*
*	complete the environnement map withh all value
*/
void		CGI::setMap( void )
{
	std::ostringstream		oss;
	HttpRequest*			req = &this->_socket->getReq();
	std::string				scriptPath = req->getPathTranslated();
	std::string				pathInfo = req->getPathInfo();
	std::string				documentRoot = scriptPath;
	size_t					cgiPos = documentRoot.find("/cgi/");
	char*					pwd = getenv("PWD");

	this->_mEnv["REDIRECT_STATUS"] = "200";
	this->_mEnv["DOCUMENT_ROOT"] = normalizePath(std::string(pwd) + "/../www");
	this->_mEnv["SCRIPT_FILENAME"] = normalizePath(std::string(pwd) + "/" + scriptPath);
	this->_mEnv["SCRIPT_NAME"] = documentRoot.substr(cgiPos);
	this->_mEnv["GATEWAY_INTERFACE"] = CGI_REVISION;
	this->_mEnv["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_mEnv["SERVER_SOFTWARE"] = SERVER_VER;
	this->_mEnv["PATH_INFO"] = req->getUri();
	this->_mEnv["PATH_TRANSLATED"] = req->getPathTranslated();
	this->_mEnv["QUERY_STRING"] = req->getQueryParams();
	this->_mEnv["REMOTE_ADDR"] = req->getRemotIp();
	this->_mEnv["REQUEST_METHOD"] = req->getMethod();

	oss << req->getContentLength();
	this->_mEnv["CONTENT_LENGTH"] = oss.str();
	oss.str("");
	oss.clear();

	if (req->getServer() && !req->getServer()->getHost().empty())
		this->_mEnv["SERVER_NAME"] = req->getServer()->getHost().front();
	
	oss << *req->getServer()->getPortList().begin();
	this->_mEnv["SERVER_PORT"] = oss.str();
	oss.str("");
	oss.clear();
	
	return ;
}

/*
 *	create a new environnement array
 */
void		CGI::setEnv( void )
{
	Map::iterator		it;
	size_t				i = 0;

	this->_aEnv = new char*[this->_mEnv.size() * 4 + 1];
	for (it = this->_mEnv.begin(); it != this->_mEnv.end(); ++it)
	{
		std::string		tmp;

		tmp = it->first + "=" + it->second;
		this->_aEnv[i++] = strdup(tmp.c_str());
	}
	this->_aEnv[i] = NULL;
	
	return ;
}

/*
 *	SetParams check if the script is a php script and complete the array with
 *	all values, for php we need just the path of the binary to execute without
 *	the script php to execute
 */
void		CGI::setParams( void )
{
	const std::string&		scriptName = getMapEnv()["SCRIPT_NAME"];
	const std::string		suffix = ".php";
	
	this->_params = new char*[4];

	this->_params[0] = strdup(this->_binaryExec.c_str());
	if (scriptName.length() >= suffix.length() &&
		scriptName.compare(scriptName.length() - suffix.length(),
							suffix.length(), suffix) == 0)
	{
		this->_params[1] = NULL;
		this->_params[2] = NULL;
		this->_params[3] = NULL;
		return ;
	}
	this->_params[1] = strdup(this->_scriptPath.c_str());
	this->_params[2] = strdup(this->_query.c_str());
	this->_params[3] = NULL;
	
	return;
}

void		CGI::checkCGI( void )
{
	if (this->_scriptPath.empty() || this->_binaryExec.empty())
		throw CGIError("empty variable on CGIobject");
	if (!_params)
		throw CGIError("array to excve empty");
	if (!_aEnv)
		throw CGIError("env array empty");
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

CGI::CGIError::CGIError( const std::string &error ) throw()
{
	this->_msg = RED"[ERROR CGI] " + error + RESET;
	return ;
}

CGI::CGIError::~CGIError( void ) throw()
{
	return ;
}

const char*		CGI::CGIError::what() const throw()
{
	return (this->_msg.c_str());
}

CGI::CGIExit::CGIExit() throw() : _msg("Cgi exit") {}

CGI::CGIExit::~CGIExit( void ) throw() {}

const char*		CGI::CGIExit::what() const throw()
{
	return (this->_msg.c_str());
}
