/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_gs.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:07:04 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/04 09:13:05 by fdehan           ###   ########.fr       */
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
 *	get the number of byte read on the buffer
 */
size_t		MyCGI::getByteRead( void )
{
	return (this->_byteRead);
}

/*
 *	get the number of byte sended on the buffer
 */
size_t		MyCGI::getByteSend( void )
{
	return (this->_byteSend);
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

bool	MyCGI::isCgiFinished() const
{
	return (this->_isExited && this->_isTransferFinished);
}

/*******************************************************************************
 *							    SETTER								    	   *
******************************************************************************/

/*
 *	reset the value of bytes read
 */
void		MyCGI::resetByteRead( void )
{
	this->_byteRead = 0;
	return ;
}
/*
 *	increase the value of byteread
 */
void		MyCGI::setByteRead( size_t bytes )
{
	this->_byteRead += bytes;
	return ;
}

/*
 *	reset the value of bytes send
 */
void		MyCGI::resetByteSend( void )
{
	this->_byteSend = 0;
	return ;
}
/*
 *	increase the value of bytesend
 */
void		MyCGI::setByteSend( size_t bytes )
{
	this->_byteSend += bytes;
	return ;
}

/*
 *	set the pid attribut
 */
void		MyCGI::setPid( pid_t pid )
{
	this->_pid = pid;
	return ;
}
