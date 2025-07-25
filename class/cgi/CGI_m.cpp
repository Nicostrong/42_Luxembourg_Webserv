/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_m.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:13:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 15:18:57 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/CGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

void		CGI::execCGI( void )
{
	char**				cmd = this->getParams();
	
	this->getSocket().getEM().monitor(this->getPipeToCGI().getIn(), 
			EPOLLOUT | EPOLLHUP | EPOLLRDHUP, *this);
	this->getSocket().getEM().monitor(this->getPipeFromCGI().getOut(), 
			EPOLLIN | EPOLLHUP | EPOLLRDHUP, *this);
				
	this->setPid(fork());

	if (this->getPid() == -1)
		throw CGIError("Fork error");
	else if (this->getPid() == 0)
	{
		Body* body = this->_socket->getReq().getBody();

		if (body)
			body->getFstream().close();
		this->getPipeToCGI().closeIn();
		this->getPipeFromCGI().closeOut();
		if (dup2(this->getPipeToCGI().getOut(), STDIN_FILENO) == -1)
			throw CGIExit();
		this->getPipeToCGI().closeOut();
		if (dup2(this->getPipeFromCGI().getIn(), STDOUT_FILENO) == -1)
			throw CGIExit();
		this->getPipeFromCGI().closeIn();
		execve(cmd[0], cmd, this->getEnv());
		throw CGIExit();
	} 
	else
	{
		this->getPipeToCGI().closeOut();
		this->getPipeFromCGI().closeIn();
	}	
	return ;
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, CGI& src_object )
{
	std::string		query = src_object.getQuery();
	char**			params = src_object.getParams();
	char**			env = src_object.getEnv();
	int				i = -1;

	out	<< MAGENTA << "[DEBUG CGI]\n================= CGI OBJECT =================" << std::endl
		<< "script to execute:" << src_object.getScriptPath() << std::endl
		<< "binary to execute:" << src_object.getBinaryPath() << std::endl
		<< "query params for CGI:" << (query.empty() ? "NULL" : query) << std::endl
		<< "arguments for execve:" << std::endl;
	while (++i < 4)
		out << "\t" << (params[i] != NULL ? params[i] : "NULL") << std::endl;
	i = -1;
	out << "env for execve:" << std::endl;
	while (env[++i])
		out << "\t" << env[i] << std::endl;
	out << "Pipe of communication with the CGI:" << std::endl;
	out << "\tPIPE IN: " << src_object.getPipeToCGI().getIn()
		<< "\tPIPE OUT: " << src_object.getPipeToCGI().getOut() << std::endl;
	out << "Pipe of communication from the CGI:" << std::endl;
	out << "\tPIPE IN: " << src_object.getPipeFromCGI().getIn()
		<< "\tPIPE OUT: " << src_object.getPipeFromCGI().getOut() << std::endl;
	out << "PID parent: " << src_object.getPid() << std::endl;
	out	<< "=================== END CGI ==================" << RESET;
	return (out);
}