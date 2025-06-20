/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/20 17:39:51 by nfordoxc         ###   Luxembourg.lu     */
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
		if (bytes == 0)
		{
			this->setIsFinish();
			em.unmonitor(fd);
			close(fd);
			return ;
		}
	}
	catch(const std::exception& e)
	{
		throw e;
		em.unmonitor(fd);
		close(fd);
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	try
	{
		if (!this->getEnd Write())
		{
			ssize_t		dataSent;
			
			dataSent = write(fd,
							this->_socket->getReq().getBody()->getBuffer().getDataUnused(), 
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
			this->getPipeToCGI().closeIn();
			em.unmonitor(fd);
			close(fd);
			return ;
		}
	}
	catch(const std::exception& e)
	{
		throw e;
		em.unmonitor(fd);
		close(fd);
	}
	return ;
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	em.unmonitor(fd);
	close(fd);
	this->setIsFinish();
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