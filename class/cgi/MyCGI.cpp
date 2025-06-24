/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:09:40 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/24 15:43:53 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
******************************************************************************/

MyCGI::MyCGI( Socket& socket )
	: _params(NULL), _aEnv(NULL), _toCGI(), _fromCGI(), _txBuffer(BUFF_SIZE),
	_rxBuffer(BUFF_SIZE), _socket(&socket), _pid(-1), _isFinish(false),
	_endWrite(false)
{
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

MyCGI::~MyCGI( void )
{
	int		i = -1;

	if (this->_params)
	{
		while (this->_params[++i])
		{
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
void		MyCGI::initMap( void )
{
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

	return ;
}

/*
 *	complete the environnement map withh all value
 */
void		MyCGI::setMap( void )
{
	std::ostringstream		oss;
	HttpRequest*			req = &this->_socket->getReq();

	this->_mEnv["AUTH_TYPE"] = "nfordoxc";
	this->_mEnv["GATEWAY_INTERFACE"] = CGI_REVISION;

	oss << req->getContentLength();
	this->_mEnv["CONTENT_LENGTH"] = oss.str();
	oss.str("");
	oss.clear();

	this->_mEnv["PATH_INFO"] = req->getPathInfo();		//	a refaire cat partit apres le script et avant le ?
	this->_mEnv["PATH_TRANSLATED"] = req->getPathTranslated();
	this->_mEnv["QUERY_STRING"] = req->getQueryParams();	//	tout ce qu il y a apres le ?
	this->_mEnv["REMOTE_ADDR"] = req->getRemotIp();

	oss << this->_socket->getSocket();
	this->_mEnv["REMOTE_IDENT"] = oss.str();
	oss.str("");
	oss.clear();

	this->_mEnv["REQUEST_METHOD"] = req->getMethod();
	this->_mEnv["SCRIPT_NAME"] = req->getCgiScript();
	if (req->getServer() && !req->getServer()->getHost().empty())
		this->_mEnv["SERVER_NAME"] = req->getServer()->getHost().front();
	
	oss << *req->getServer()->getPortList().begin();
	this->_mEnv["SERVER_PORT"] = oss.str();
	oss.str("");
	oss.clear();

	this->_mEnv["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_mEnv["SERVER_SOFTWARE"] = SERVER_VER;
	
	return ;
}

/*
 *	create a new environnement array
 */
void		MyCGI::setEnv( void )
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

void		MyCGI::setParams( void )
{
	this->_params = new char*[4];

	this->_params[0] = strdup(this->_binaryExec.c_str());
	this->_params[1] = strdup(this->_scriptPath.c_str());
	this->_params[2] = strdup(this->_query.c_str());
	this->_params[3] = NULL;
	
	return;
}

void		MyCGI::checkCGI( void )
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

MyCGI::CGIError::CGIError( const std::string &error ) throw()
{
	this->_msg = RED"[ERROR CGI] " + error + RESET;
	return ;
}

MyCGI::CGIError::~CGIError( void ) throw()
{
	return ;
}

const char*		MyCGI::CGIError::what() const throw()
{
	return (this->_msg.c_str());
}