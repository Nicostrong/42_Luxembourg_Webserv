/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 17:10:41 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BaseData.hpp"
#include "../includes/ClientData.hpp"

BaseData::BaseData(int fd, BaseDataType type) : _fd(fd), _type(type) {}

BaseData::BaseData(const BaseData &obj) : _fd(obj._fd),  _type(obj._type) {}

BaseData::~BaseData() {}
		
BaseData &BaseData::operator=(const BaseData &obj)
{
	(void)obj;
	return (*this);
}

int BaseData::getFd() const
{
	return (this->_fd);
}

BaseData::BaseDataType BaseData::getType() const
{
	return (this->_type);
}

BaseData *BaseData::getHerited(int fd, BaseDataType type)
{
	switch (type)
	{
		case CLIENT:
			return (new ClientData(fd));
		
		default:
			return (new BaseData(fd, type));
	}
}

