/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:49 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 09:20:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTDATA_HPP
#define CLIENTDATA_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include "BaseData.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


class ClientData : public BaseData
{
	public:
		ClientData();
		ClientData(const ClientData &obj);
		~ClientData();
		ClientData &operator=(const ClientData &obj);
		
		HttpRequest &getRequest();
		HttpResponse &getResponse();
	private:
		HttpRequest _request;
		HttpResponse _response;
};

#endif