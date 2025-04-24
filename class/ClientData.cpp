/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:34:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 09:20:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ClientData.hpp"
#include "../includes/BaseData.hpp"

ClientData::ClientData() : BaseData(CLIENT), _request(HttpRequest()) {}

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