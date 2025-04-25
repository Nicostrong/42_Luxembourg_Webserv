/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:49 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/25 14:42:28 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTDATA_HPP
#define CLIENTDATA_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include "EventHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


class ClientData : public EventHandler
{
	public:
		ClientData(int fd);
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