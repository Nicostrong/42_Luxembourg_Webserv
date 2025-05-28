/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:20:30 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 20:14:09 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/RequestBody.hpp"

RequestBody::RequestBody() : _buff(RAM_BUFF), _size(0)
{
	
}

RequestBody::~RequestBody() 
{
	if (this->_fBuff.is_open())
	{
		std::remove(this->_fName.c_str());
	}
}

void RequestBody::add(Buffer& buff)
{
	if (this->_size < RAM_BUFF)
	{
		if (buff.getBufferUnread() < 1)
			return ;
		
		size_t len = std::min(buff.getBufferUnread(), 
			RAM_BUFF - this->_buff.getBufferUsed());
			
		this->_buff.copyFrom(buff, this->_buff.getBufferRead(), len);
		buff.setBufferRead(len);
	}

	if (buff.getBufferUnread() < 1)
		return ;

	openTmpFile();
	
	
}

void RequestBody::openTmpFile()
{
	std::stringstream ss;

	if (this->_fBuff.is_open())
		return ;
	
	for (int i = 0; !this->_fBuff.is_open() && i < MAX_CLIENT; ++i)
	{
		ss << TMP_PATH << "webserv_" << i;
		this->_fBuff.open(ss.str(), 
			std::ios::in | std::ios::out | std::ios::trunc);
	}
	
	if (!this->_fBuff.is_open())
		throw std::runtime_error("Cannot create a tmp file");
	
	this->_fName = ss.str();
}
