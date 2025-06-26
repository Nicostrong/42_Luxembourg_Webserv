/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/26 09:39:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		MyCGI::onReadEvent(int fd, EventMonitoring& em)
{
	try
	{
		ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
			this->_rxBuffer.getBufferUnused());
		
		std::cout << "DEBUG CGI on READ" << std::endl;
		std::cout << "nb bytes lu: " << bytes << std::endl;
		
		if (bytes == -1)
			throw CGIError("Error reading pipe from GCI");
			
		this->_rxBuffer.setBufferUsed(bytes);
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		if (bytes == 0)
		{
			this->setIsFinish();
			this->_socket->getHandler().getCgiResponse().setEofReceived();
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
		cgiResp->setError();
		cgiResp->setErrorCode(HttpBase::INTERNAL_SERVER_ERROR);
		this->getPipeFromCGI().closeOut();
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	LOG_DEB("ON WRITE");
	/*
		on ecrit le buffer dans le pipe et on set la variable _endWrite
		ce qui permet le children
	*/
	static size_t	nbByte = 0;
	try
	{
		if (!this->getEndWrite())
		{
			ssize_t		dataSent;
			Body* 		body = this->_socket->getReq().getBody();
			bool 		eof = false;

			if (body)
			{
				std::cout << "Request for children" << std::endl;
				LOG_DEB("BUFFER BODY: " << body->getBuffer().getDataUnread());
				
				body->read(this->_txBuffer);

				dataSent = write(fd,
							this->_txBuffer.getDataUnread(), 
							this->_txBuffer.getBufferUnread());
				/*dataSent = write(fd,
							body->getBuffer().getDataUnread(), 
							body->getBuffer().getBufferUnread());*/

				nbByte += dataSent;
				LOG_DEB("TAILLE DU BODY: " << body->getSize());
				LOG_DEB("NUMBER OF BYTE WRITE: " << nbByte);
				eof = (body->getSize() == nbByte);
				std::cout << "EOF : " << (eof ? "TRUE" : " FALSE") << std::endl;
				if (dataSent == -1)
					throw CGIError("send data on pipe failed");
				this->_txBuffer.setBufferRead(dataSent);
			}
			
			if (!body || (eof && this->_txBuffer.isBufferRead()))
			{
				LOG_DEB("EOF of the body");
				std::cout << "NB TOTAL DE BYTES WRITE: " << nbByte << std::endl;
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
		std::cerr << e.what() << std::endl;
		throw e;
	}
	return ;
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	if (this->getPipeFromCGI().getOut() == fd)
	{
		this->_socket->getHandler().getCgiResponse().setEofReceived();
		this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
		em.unmonitor(fd);
		this->getPipeFromCGI().closeOut();
		this->setIsFinish();
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