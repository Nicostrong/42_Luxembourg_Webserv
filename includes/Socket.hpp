/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:29 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 23:03:00 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "./HttpRequest.hpp"
# include "./HttpResponse.hpp"


# include "./ResponseHandling.hpp"
# include "./IEventHandler.hpp"
# include "./EventMonitoring.hpp"
# include "./File.hpp"
# include "./Buffer.hpp"
# include "./HttpExceptions.hpp"
# include "./HttpSevereExceptions.hpp"

# define RX_SIZE 1024

class Server;

class Socket : public IEventHandler
{
	public:
		class SocketReadException : public std::exception
		{
			public:
				const char* what() const throw();
		};
	
		Socket(int fd, EventMonitoring&	em, Server& ctx, 
			const sockaddr_in& sockAddr);
		Socket(const Socket& obj);
		~Socket();
		Socket& 			operator=(const Socket& obj);
		bool 				operator==(const Socket& obj);
		int					getSocket() const;
		HttpRequest&		getReq();
		HttpResponse&		getResp();
		Server& 			getCtx();
		Buffer&				getTxBuffer();
		EventMonitoring&	getEventMonitoring();
		void				reset();
		void				onReadEvent(int fd, int type, EventMonitoring& em);
		void				onWriteEvent(int fd, int type, EventMonitoring& em);
		void				onCloseEvent(int fd, int type, EventMonitoring& em);
		static std::string 				getReadableIp(
			const struct sockaddr_in& addr);
	private:
		const int			_fd;
		HttpRequest 		_req;
		HttpResponse 		_resp;
		EventMonitoring&	_em;
		Server&				_ctx;
		std::string			_remoteIp;
		Buffer				_rxBuffer;
		Buffer				_txBuffer;
		bool				_reset;
		bool				_keepAlive;
		ResponseHandling	_rHandler;
		
		
};

#endif