/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:54:35 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 17:31:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BaseData.hpp"
#include "../includes/ClientData.hpp"

BaseData::BaseData(BaseDataType type) : _type(type) {}

BaseData::BaseData(const BaseData &obj) : _type(obj._type) {}

BaseData::~BaseData() {}
		
BaseData &BaseData::operator=(const BaseData &obj)
{
	(void)obj;
	return (*this);
}

BaseData::BaseDataType BaseData::getType() const
{
	return (this->_type);
}

BaseData *BaseData::getHerited(BaseDataType type)
{
	switch (type)
	{
		case CLIENT:
			return (new ClientData());
		
		default:
			return (new BaseData(type));
	}
}

