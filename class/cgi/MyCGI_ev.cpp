/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/26 16:00:02 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cgi/MyCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void		MyCGI::onReadEvent(int fd, EventMonitoring& em)
{
	static size_t	totalRead = 0;

	LOG_DEB("Read event");
	try
	{
		if (getEndWrite())
		{
			ssize_t		bytes = read(fd, this->_rxBuffer.getDataUnused(), 
										this->_rxBuffer.getBufferUnused());
			
			totalRead += bytes;

			std::cout << "DEBUG CGI on READ" << std::endl;
			std::cout << "nb bytes lu: " << bytes << std::endl;
			std::cout << "TOTAL READ: " << totalRead << std::endl;
			
			if (bytes == -1)
				throw CGIError("Error reading pipe from GCI");
			
			this->_rxBuffer.setBufferUsed(bytes);
			LOG_DEB("RESPONCE CGI: " << std::endl << this->getRxBuffer().getDataUnread() << std::endl);
			this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
			LOG_DEB("RESPONCE CGI: " << std::endl << this->getRxBuffer().getDataUnread() << std::endl);
			if (bytes == 0)
			{
				this->setIsFinish();
				this->_socket->getHandler().getCgiResponse().setEofReceived();
				this->_socket->getHandler().getCgiParser().onRead(this->_rxBuffer, *this->_socket);
				em.unmonitor(fd);
				this->getPipeFromCGI().closeOut();
				resetByteRead();
				return ;
			}
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
	try
	{
		LOG_DEB(*this);
		if (!this->getEndWrite())
		{
			ssize_t		dataSent;
			Body* 		body = this->_socket->getReq().getBody();
			bool 		eof = false;

			if (body)
			{
				body->read(this->_txBuffer);
				//LOG_DEB("BUFFER BODY: " << std::endl << this->getTxBuffer().getDataUnread() << std::endl);
				dataSent = write(fd,
							this->_txBuffer.getDataUnread(), 
							this->_txBuffer.getBufferUnread());

				setByteRead(dataSent);
				LOG_DEB("TAILLE DU BODY: " << body->getSize());
				LOG_DEB("NUMBER OF BYTE WRITE: " << getByteRead());
				eof = (body->getSize() == getByteRead());
				std::cout	<< "body size: " << body->getSize()
							<< "bytes read: " << getByteRead()
							<< std::endl;
				std::cout << "EOF : " << (eof ? "TRUE" : " FALSE") << std::endl;
				if (dataSent == -1)
					throw CGIError("send data on pipe failed");
				this->_txBuffer.setBufferRead(dataSent);
			}
			
			if (!body || (eof && this->_txBuffer.isBufferRead()))
			{
				this->setEndWrite();
				em.unmonitor(fd);
				this->getPipeToCGI().closeIn();
				this->_socket->getHandler().setState(HttpHandling::CGI_RECEIVING);
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