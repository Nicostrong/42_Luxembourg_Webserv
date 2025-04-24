/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:34:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 17:10:36 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ClientData.hpp"
#include "../includes/BaseData.hpp"

ClientData::ClientData(int fd) : BaseData(fd, CLIENT), _request(HttpRequest()) 
	{}

ClientData::ClientData(const ClientData &obj) : BaseData(obj)
, _request(HttpRequest())
{
	*this = obj;
}

ClientData::~ClientData() {}

ClientData &ClientData::operator=(const ClientData &obj)
{
	if (this != &obj)
		this->_request = obj._request;
	return (*this);
}

HttpRequest &ClientData::getRequest()
{
	return (this->_request);
}

HttpResponse &ClientData::getResponse()
{
	return (this->_response);
}