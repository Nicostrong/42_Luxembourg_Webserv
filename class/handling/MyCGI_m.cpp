/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:13:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/19 16:08:29 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								METHOD										   *
******************************************************************************/

void		MyCGI::execCGI( void )
{
	EventMonitoring		em = this->getSocket().getEM();
	char**				cmd = this->getParams();

	//std::cout << "SOCKET: " << this->getSocket();
	
	em.monitor(this->_toCGI.getIn(), POLLIN | POLLHUP | POLLRDHUP, *this);
				
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

/*std::ostream	&operator<<( std::ostream &out, MyCGI const &src_object )
{	
	out	<< CYAN << "================= MYCGI OGJECT =================" << RESET << std::endl
		<< CYAN << "script to execute:" << src_object.get<< std::endl;
		
	out	<< GREEN << "=================== END SERVER ==================" << RESET << std::endl;
	return (out);
}*/