/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCGI_ev.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:40:58 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/19 15:32:24 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/handling/HandleCGI.hpp"
#include "../../includes/networking/Socket.hpp"

/*******************************************************************************
 *							SERVER EVENTS									   *
******************************************************************************/

void		HandleCGI::onReadEvent(int fd, int type, EventMonitoring& em)
{
	(void)type;

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
		this->_handler->onRead(em, this->_socket);	
		if (this->_rxBuffer.isBufferRead())
			this->_endRead = true;
	}
	catch(const std::exception& e)
	{
		LOG_DEB(e.what());
		em.unmonitor(fd);
		close(fd);
	}
	if (this->_endRead)
	{
		em.unmonitor(fd);
		close(fd);
	}
	return ;
}

void		HandleCGI::onWriteEvent(int fd, int type, EventMonitoring& em)
{
	(void)type;

	try
	{
		//this->_txBuffer.resetIfRead();
		this->_handler->onWrite(em, this->_socket);

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
		em.monitor(this->_dataFromCGI.getOut(), POLLOUT | POLLHUP | POLLRDHUP,
				EventData::CLIENT, *this);
	}
	return ;
}

void		HandleCGI::onCloseEvent(int fd, int type, EventMonitoring& em)
{
	(void)fd;
	(void)type;
	(void)em;
	
	em.unmonitor(fd);
	close(fd);
	this->_input.clear();
	this->_output.clear();

	return ;
}

void HandleCGI::onTickEvent( int fd, EventMonitoring& em )
{
	(void)fd;
	(void)em;
}