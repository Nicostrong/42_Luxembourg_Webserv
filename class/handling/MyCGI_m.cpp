/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_m.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:13:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/19 13:58:12 by nfordoxc         ###   Luxembourg.lu     */
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
	
	em.monitor(this->_toCGI.getIn(), POLLIN | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
				
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
/*
std::ostream	&operator<<( std::ostream &out, MyCGI const &src_object )
{	
	out	<< CYAN << "================= MYCGI OGJECT =================" << RESET << std::endl
		<< CYAN << "script to execute:" << src_object.get<< std::endl;
		
	for (itHost = hosts.begin(); itHost != hosts.end(); ++itHost)
		out << "\t- " << *itHost << std::endl;

	out << RESET <<std::endl
		<< GREEN << "Listen adress:\n\t" << src_object.getIp().getIpString() << RESET << std::endl
		<< GREEN << "Listen port:" << RESET << std::endl;
	for ( itPort = ports.begin(); itPort != ports.end(); ++itPort)
   		out << GREEN << "\t- " << *itPort << RESET << std::endl;
	out << GREEN << "Root path:\n\t" << src_object.getPath() << RESET << std::endl
		<< GREEN << "Index file:\n\t" << src_object.getIndex() << RESET << std::endl
		<< GREEN << "Max connection client:\n\t" << src_object.getMaxClient() << RESET << std::endl
		<< GREEN << "Max size of body:\n\t" << src_object.getMaxSizeBody() << " bytes." << RESET << std::endl
		<< GREEN << "Error pages:" << RESET << std::endl;
	
	for (it = mError.begin(); it != mError.end(); ++it)
		out << GREEN << "\t" << it->first << " => " << it->second << RESET << std::endl;
	
	out << GREEN << "Locations:" << RESET << std::endl;	
	for (std::map<std::string, Location *>::const_iterator it = loc.begin(); it != loc.end(); ++it)
		out << *it->second << RESET << std::endl;
	out	<< GREEN << "=================== END SERVER ==================" << RESET << std::endl;
	return (out);
}*/