/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/25 12:34:23 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
******************************************************************************/

void		MyCGI::onReadEvent(int fd, EventMonitoring& em)
{
	LOG_DEB("Read ev");
	try
	{
		ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
			this->_rxBuffer.getBufferUnused());
		//throw std::exception();
		std::cout << "DEBUG CGI on READ" << std::endl;
		std::cout << "nb bytes lu: " << bytes << std::endl;
		
		if (bytes == -1)
			throw CGIError("Error reading pipe from GCI");
			
		this->_rxBuffer.setBufferUsed(bytes);
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		std::cout << this->_rxBuffer;
		if (bytes == 0)
		{
			this->setIsFinish();
			this->_socket->getHandler().getCgiResponse().setEofReceived();
			this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
			em.unmonitor(fd);
			this->getPipeFromCGI().closeOut();
			return ;
		}
	}
	catch(const std::exception& e)
	{
		CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

		this->setIsFinish();
		em.unmonitor(fd);
		this->_socket->getHandler().getCgiResponse().setEofReceived();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		cgiResp->setError();
		cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
		this->getPipeFromCGI().closeOut();
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	LOG_DEB("Write ev");
	try
	{
		int status;

		if (!this->getEndWrite())
		{
			ssize_t		dataSent;
			Body* 		body = this->_socket->getReq().getBody();
			bool 		eof = false;

			if (body)
			{
				eof = body->read(this->_txBuffer);
				std::cout << "Body of Req" << std::endl;
				std::cout << this->_txBuffer << std::endl;
				LOG_DEB("Fd " << this->_toCGI.getIn());
				LOG_DEB(waitpid(this->getPid(), &status, WNOHANG));
				dataSent = write(fd,
							this->_txBuffer.getDataUnread(), 
							this->_txBuffer.getBufferUnread());
			
				std::cout << "DEBUG CGI on WRITE" << std::endl;
				std::cout << "nb bytes ecrit: " << dataSent << std::endl;
				if (dataSent == -1)
					throw CGIError("send data on pipe failed");
				this->_txBuffer.setBufferRead(dataSent);
				LOG_DEB("Is read " << this->_txBuffer.isBufferRead());
			}
			
			if (!body || (eof && this->_txBuffer.isBufferRead()))
			{
				this->setEndWrite();
				this->_socket->getHandler().getCgiResponse().setEofReceived();
				this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
				em.unmonitor(fd);
				this->getPipeToCGI().closeIn();
				return ;
			}
			
		}
	}
	catch(const std::exception& e)
	{
		CgiResponse* cgiResp = &this->_socket->getHandler().getCgiResponse();

		em.unmonitor(fd);
		cgiResp->setError();
		cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
		this->getPipeToCGI().closeIn();
	}
	return ;
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	LOG_DEB("Close ev");
	if (this->getPipeFromCGI().getOut() == fd)
	{
		this->_socket->getHandler().getCgiResponse().setEofReceived();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		em.unmonitor(fd);
		this->getPipeFromCGI().closeOut();
		this->setIsFinish();
	}

	if (this->getPipeToCGI().getIn() == fd)
	{
		em.unmonitor(fd);
		this->getPipeToCGI().closeIn();
	}
	
	return ;
}

void		MyCGI::onTickEvent( int fd, EventMonitoring& em )
{
	int		status;

	(void)fd;
	(void)em;
	if (waitpid(this->getPid(), &status, WNOHANG))
		this->setIsFinish();
	return ;
}