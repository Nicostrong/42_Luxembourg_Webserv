/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/21 09:52:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/handling/MyCGI.hpp"
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
			this->_socket->getHandler().getResponseHandling().init(*this->_socket);
			em.monitorUpdate(this->_socket->getSocket(), EPOLLOUT | EPOLLHUP | EPOLLRDHUP);
			return ;
		}
	}
	catch(const std::exception& e)
	{
		throw e;
		em.unmonitor(fd);
		this->getPipeFromCGI().closeOut();
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	try
	{
		if (!this->getEndWrite())
		{
			ssize_t		dataSent;
			
			dataSent = write(fd,
							this->_txBuffer.getDataUnread(), 
							this->_txBuffer.getBufferUnread());
			
			std::cout << "DEBUG CGI on WRITE" << std::endl;
			std::cout << "nb bytes ecrit: " << dataSent << std::endl;
			if (dataSent == -1)
				throw CGIError("send data on pipe failed");
			this->_txBuffer.setBufferRead(dataSent);
		}
		if (this->_txBuffer.isBufferRead())
		{
			this->setEndWrite();
			em.unmonitor(fd);
			this->getPipeToCGI().closeIn();
			return ;
		}
	}
	catch(const std::exception& e)
	{
		throw e;
		em.unmonitor(fd);
		this->getPipeToCGI().closeIn();
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
		this->_socket->getHandler().getResponseHandling().init(*this->_socket);
		em.monitorUpdate(this->_socket->getSocket(), EPOLLOUT | EPOLLHUP | EPOLLRDHUP);
		this->setIsFinish();
	}
	
	return ;
}

void		MyCGI::onTickEvent( int fd, EventMonitoring& em )
{
	int		status;

	std::cout << waitpid(this->getPid(), &status, WNOHANG) << std::endl;
	(void)fd;
	(void)em;
	if (waitpid(this->getPid(), &status, WNOHANG))
		this->setIsFinish();
	return ;
}