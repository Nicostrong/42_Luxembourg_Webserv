/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_gs.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:07:04 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 15:19:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/CGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *								GETTER										   *
******************************************************************************/

/*
 *	get the path of the script to execute
 */
std::string&		CGI::getScriptPath( void )
{
	return (this->_scriptPath);
}

/*
 *	get the path of the binary to execute
 */
std::string&		CGI::getBinaryPath( void )
{
	return (this->_binaryExec);
}

/*
 *	get the query string of the request
 */
std::string&	CGI::getQuery( void )
{
	return (this->_query);
}

/*
 *	get the number of byte read on the buffer
 */
size_t		CGI::getByteRead( void )
{
	return (this->_byteRead);
}

/*
 *	get the number of byte sended on the buffer
 */
size_t		CGI::getByteSend( void )
{
	return (this->_byteSend);
}

/*
 *	get all parameters in an array
 */
char**		CGI::getParams( void )
{
	return (this->_params);
}

/*
 *	geet all environnement variable in an array
 */
char**		CGI::getEnv( void )
{
	return (this->_aEnv);
}

/*
 *	get the Pipe objet to communicate with the CGI
 */
Pipe&			CGI::getPipeToCGI( void )
{
	return (this->_toCGI);
}

/*
 *	get the Pipe objet using by the  CGI
 */
Pipe&			CGI::getPipeFromCGI( void )
{
	return (this->_fromCGI);
}

/*
 *	get the Buffer to communicate with the CGI
 */
Buffer&			CGI::getTxBuffer( void )
{
	return (this->_txBuffer);
};

/*
 *	get the Buffer from the CGI
 */
Buffer&			CGI::getRxBuffer( void )
{
	return (this->_rxBuffer);
};

/*
 *	return the Socket object
 */
Socket&		CGI::getSocket( void )
{
	return (*this->_socket);
}

/*
 *	get the map of environnement variable
 */
CGI::Map&		CGI::getMapEnv( void )
{
	return (this->_mEnv);
}

/*
 *	get the pid of the parent
 */
pid_t		CGI::getPid( void )
{
	return (this->_pid);
}

bool	CGI::isCgiFinished() const
{
	return (this->_isExited && this->_isTransferFinished);
}

bool	CGI::isOutputFinished() const
{
	return (this->_isTransferFinished);
}

/*******************************************************************************
 *							    SETTER								    	   *
******************************************************************************/

/*
 *	reset the value of bytes read
 */
void		CGI::resetByteRead( void )
{
	this->_byteRead = 0;
	return ;
}
/*
 *	increase the value of byteread
 */
void		CGI::setByteRead( size_t bytes )
{
	this->_byteRead += bytes;
	return ;
}

/*
 *	reset the value of bytes send
 */
void		CGI::resetByteSend( void )
{
	this->_byteSend = 0;
	return ;
}
/*
 *	increase the value of bytesend
 */
void		CGI::setByteSend( size_t bytes )
{
	this->_byteSend += bytes;
	return ;
}

/*
 *	set the pid attribut
 */
void		CGI::setPid( pid_t pid )
{
	this->_pid = pid;
	return ;
}
