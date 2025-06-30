/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:13:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/30 10:09:01 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								METHOD										   *
 ******************************************************************************/

void		MyCGI::execCGI( void )
{
	char**				cmd = this->getParams();
	
	//LOG_DEB(*this);
	this->getSocket().getEM().monitor(this->getPipeToCGI().getIn(), 
			EPOLLOUT | EPOLLHUP | EPOLLRDHUP, *this);
	this->getSocket().getEM().monitor(this->getPipeFromCGI().getOut(), 
			EPOLLIN | EPOLLTICK | EPOLLHUP | EPOLLRDHUP, *this);
				
	this->setPid(fork());

	if (this->getPid() == -1)
		throw CGIError("Pipe error");
	else if (this->getPid() == 0)
	{
		this->getPipeToCGI().closeIn();											//	on ferme le pipe=>P d ecriture du parent
		this->getPipeFromCGI().closeOut();										//	on ferme le pipe=>C de lecture du gosse
		if (dup2(this->getPipeToCGI().getOut(), STDIN_FILENO) == -1)
			throw CGIError("dup2 IN");
		this->getPipeToCGI().closeOut();										//	on ferme le pipe apres dup2 STDIN
		if (dup2(this->getPipeFromCGI().getIn(), STDOUT_FILENO) == -1)
			throw CGIError("dup2 OUT");
		this->getPipeFromCGI().closeIn();										//	on ferme le pipe apres dup2 STDOUT
		execve(cmd[0], cmd, this->getEnv());
		throw CGIError("execve error");
	} 
	else
	{
		this->getPipeToCGI().closeOut();										//	on ferme le pipe=>P de lecture pour le gosse
		this->getPipeFromCGI().closeIn();										//	on ferme le pipe=>C d ecriture du gosse
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
	std::string		query = src_object.getQuery();
	char**			params = src_object.getParams();
	char**			env = src_object.getEnv();
	int				i = -1;

	out	<< MAGENTA << "[DEBUG CGI]\n================= MYCGI OBJECT =================" << std::endl
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
	out	<< "=================== END MYCGI ==================" << RESET;
	return (out);
}