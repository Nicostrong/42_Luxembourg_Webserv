/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:29 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/04 17:17:48 by fdehan           ###   ########.fr       */
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
# include "./server/ServerManager.hpp"
# include "./Ip.hpp"

# define RX_SIZE 1024

class SocketManager;

class Socket : public IEventHandler
{
	public:
		class SocketReadException : public std::exception
		{
			public:
				const char* what() const throw();
		};
	
		Socket(int fd, const std::pair<Ip, size_t>& sockAddr,
				ServerManager& sm, SocketManager& sockm);
		~Socket();
		
		bool 				operator==(const Socket& obj);
		int					getSocket() const;
		HttpRequest&		getReq();
		HttpResponse&		getResp();
		Buffer&				getTxBuffer();
		ServerManager&		getSM();
		void				reset();
		void				onReadEvent(int fd, int type, EventMonitoring& em);
		void				onWriteEvent(int fd, int type, EventMonitoring& em);
		void				onCloseEvent(int fd, int type, EventMonitoring& em);
	private:
		Socket(const Socket& obj);
		Socket& 			operator=(const Socket& obj);

		const int					_fd;
		const std::pair<Ip, size_t> _sockAddr;
		HttpRequest 				_req;
		HttpResponse 				_resp;
		Buffer						_rxBuffer;
		Buffer						_txBuffer;
		bool						_reset;
		bool						_keepAlive;
		ResponseHandling			_rHandler;
		ServerManager&				_sm;
		SocketManager&				_sockm;
};

#endif