/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_gs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:07:04 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/24 08:41:01 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								GETTER										   *
******************************************************************************/

/*
 *	get the path of the script to execute
 */
std::string&		MyCGI::getScriptPath( void )
{
	return (this->_scriptPath);
}

/*
 *	get the path of the binary to execute
 */
std::string&		MyCGI::getBinaryPath( void )
{
	return (this->_binaryExec);
}

/*
 *	get the query string of the request
 */
std::string&	MyCGI::getQuery( void )
{
	return (this->_query);
}

/*
 *	get all parameters in an array
 */
char**		MyCGI::getParams( void )
{
	return (this->_params);
}

/*
 *	geet all environnement variable in an array
 */
char**		MyCGI::getEnv( void )
{
	return (this->_aEnv);
}

/*
 *	get the Pipe objet to communicate with the CGI
 */
Pipe&			MyCGI::getPipeToCGI( void )
{
	return (this->_toCGI);
}

/*
 *	get the Pipe objet using by the  CGI
 */
Pipe&			MyCGI::getPipeFromCGI( void )
{
	return (this->_fromCGI);
}

/*
 *	get the Buffer to communicate with the CGI
 */
Buffer&			MyCGI::getTxBuffer( void )
{
	return (this->_txBuffer);
};

/*
 *	get the Buffer from the CGI
 */
Buffer&			MyCGI::getRxBuffer( void )
{
	return (this->_rxBuffer);
};

/*
 *	return the Socket object
 */
Socket&		MyCGI::getSocket( void )
{
	return (*this->_socket);
}

/*
 *	get the map of environnement variable
 */
MyCGI::Map&		MyCGI::getMapEnv( void )
{
	return (this->_mEnv);
}

/*
 *	get the pid of the parent
 */
pid_t		MyCGI::getPid( void )
{
	return (this->_pid);
}

/*
 *	get the checker if the CGI is finish
 */
bool		MyCGI::getIsFinish( void )
{
	return (this->_isFinish);
}

/*
 *	get the checker if all data are sending to the CGI
 */
bool		MyCGI::getEndWrite( void )
{
	return (this->_endWrite);
}

/*******************************************************************************
 *							    SETTER								    	   *
******************************************************************************/

/*
 *	set the pid attribut
 */
void		MyCGI::setPid( pid_t pid )
{
	this->_pid = pid;
	return ;
}

void		MyCGI::setIsFinish( bool value )
{
	this->_isFinish = value;
	return ;
}

void		MyCGI::setEndWrite( bool value )
{
	this->_endWrite = value;
	return ;
}
