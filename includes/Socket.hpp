/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:29 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/08 16:16:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#include "IEventHandler.hpp"
#include "EventMonitoring.hpp"

class Server;

class Socket : public IEventHandler
{
	public:
		Socket(int fd, EventMonitoring&	em, Server& ctx);
		Socket(const Socket& obj);
		~Socket();
		Socket& 	operator=(const Socket& obj);
		bool 		operator==(const Socket& obj);
		int			getSocket() const;
		std::string getRemoteIp() const;
		void		onReadEvent(int fd, int type, EventMonitoring& em);
		void		onWriteEvent(int fd, int type, EventMonitoring& em);
		void		onCloseEvent(int fd, int type, EventMonitoring& em);
	private:
		const int			_fd;
		HttpRequest 		_req;
		HttpResponse 		_resp;
		EventMonitoring&	_em;
		Server&				_ctx;
		std::string			_remoteIp;
		std::string			_remoteHost;
	
};

#endif