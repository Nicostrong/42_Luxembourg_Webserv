/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:13:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/20 16:09:03 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								METHOD										   *
******************************************************************************/

void		MyCGI::execCGI( void )
{
	char**				cmd = this->getParams();
	
	this->getSocket().getEM().monitor(this->_toCGI.getIn(), POLLIN | POLLHUP | POLLRDHUP, *this);
				
	this->setPid(fork());

	if (this->getPid() == -1)
	{
		std::cerr << "fork failed\n"; 
		return ;
	}
	else if (this->getPid() == 0)
	{
		this->getPipeToCGI().closeIn();
		this->getPipeFromCGI().closeOut();
		if (dup2(this->getPipeToCGI().getOut(), STDIN_FILENO) == -1)
			std::runtime_error("[ERROR] dup2 IN");
		this->getPipeToCGI().closeOut();
		if (dup2(this->getPipeFromCGI().getIn(), STDOUT_FILENO) == -1)
			std::runtime_error("[ERROR] dup2 IN");
		this->getPipeFromCGI().closeIn();
		execve(cmd[0], cmd, this->getEnv());
		std::cerr << "ERROR execve\n";
		exit(EXIT_FAILURE);	//!\\ LEAKS
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
std::ostream	&operator<<( std::ostream &out, MyCGI& src_object )
{
	char**		params = src_object.getParams();
	char**		env = src_object.getEnv();
	int			i = -1;

	out	<< MAGENTA << "[DEBUG CGI]\n================= MYCGI OBJECT =================" << std::endl
		<< "script to execute:" << src_object.getScriptPath()<< std::endl
		<< "binary to execute:" << src_object.getBinaryPath()<< std::endl
		<< "query params for CGI:" << src_object.getQuery()<< std::endl;
	while (*params[++i])
		out << "\t" << params[i] << std::endl;
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
	out	<< "=================== END MYCGI ==================" << RESET;
	return (out);
}