/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI_ev.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/19 15:51:13 by nfordoxc         ###   Luxembourg.lu     */
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
		//this->_rxBuffer.resetIfRead();

		ssize_t		bytes = recv(fd, this->_rxBuffer.getDataUnused(), 
			this->_rxBuffer.getBufferUnused(), 0);
		
		std::cout << "DEBUG CGI on READ" << std::endl;
		std::cout << "nb bytes lu: " << bytes << std::endl;
		
		if (bytes == -1)
			throw std::runtime_error("Error reading pipe from GCI");
			
		this->_rxBuffer.setBufferUsed(bytes);
		if (this->_rxBuffer.isBufferRead())
			this->_isFinish = true;
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		em.unmonitor(fd);
		close(fd);
	}
	if (this->_isFinish)
	{
		em.unmonitor(fd);
		close(fd);
	}
	return ;
}

void		MyCGI::onWriteEvent(int fd, EventMonitoring& em)
{
	try
	{
		//this->_txBuffer.resetIfRead();

		if (!this->_txBuffer.isBufferRead())
		{
			int		dataSent;
			
			dataSent = send(fd,
							this->_socket->getReq().getBody()->getBuffer().getDataUnused(), 
							this->_txBuffer.getBufferUnread(), 0);
			
			std::cout << "DEBUG CGI on WRITE" << std::endl;
			std::cout << "nb bytes ecrit: " << dataSent << std::endl;
			if (dataSent == -1)
				throw std::runtime_error("send failed");
			this->_txBuffer.setBufferRead(dataSent);
			LOG_DEB(dataSent);
		}
		if (this->_txBuffer.isBufferRead())
			this->_endWrite = true;
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		em.unmonitor(fd);
		close(fd);
	}
	if (this->_endWrite)
	{
		em.unmonitor(fd);
		close(fd);
		em.monitor(this->_fromCGI.getOut(), POLLOUT | POLLHUP | POLLRDHUP, *this);
	}
	return ;
}

void		MyCGI::onCloseEvent(int fd, EventMonitoring& em)
{
	em.unmonitor(fd);
	close(fd);
	return ;
}

void		MyCGI::onTickEvent( int fd, EventMonitoring& em )
{
	(void)fd;
	(void)em;
	return ;
}