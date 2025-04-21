/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:49 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 22:18:53 by fdehan           ###   ########.fr       */
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


class ClientData : public BaseData
{
	public:
		class SocketReadException : public std::exception {
			public:
				const char * what ();
		};
		
		ClientData();
		ClientData(const ClientData &obj);
		~ClientData();
		ClientData &operator=(const ClientData &obj);
		
		HttpRequest &getRequest();
	private:
		HttpRequest _request;

};

#endif