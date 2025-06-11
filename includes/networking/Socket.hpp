/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:29 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/11 09:34:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "./../lib.hpp"
# include "./../utils/Buffer.hpp"
# include "./../utils/File.hpp"
# include "./../utils/Ip.hpp"
# include "./../utils/Endpoint.hpp"
# include "./../events/IEventHandler.hpp"
# include "./../events/EventMonitoring.hpp"
# include "./../server/ServerManager.hpp"
# include "./../http/HttpRequest.hpp"
# include "./../http/HttpResponse.hpp"
# include "./../http/HttpExceptions.hpp"
# include "./../http/HttpSevereExceptions.hpp"
# include "./../handling/ResponseHandling.hpp"
# include "./../http/HttpHandling.hpp"

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
	
		Socket(int fd, const Endpoint& sockAddr, const Endpoint& entryAddr,
				ServerManager& sm, SocketManager& sockm);
		~Socket();
		
		bool 				operator==(const Socket& obj);
		int					getSocket() const;
		const Endpoint&		getSockAddr() const;
		const Endpoint&		getEntryAddr() const;
		HttpRequest&		getReq();
		HttpResponse&		getResp();
		Buffer&				getRxBuffer();
		Buffer&				getTxBuffer();
		ServerManager&		getSM();
		EventMonitoring&	getEM( void );
		HttpHandling&		getHandler();
		void 				setSocketClose();
		void				setReset();
		void				reset(EventMonitoring& em);
		void				onReadEvent(int fd, int type, EventMonitoring& em);
		void				onWriteEvent(int fd, int type, EventMonitoring& em);
		void				onCloseEvent(int fd, int type, EventMonitoring& em);
		void				setEM( EventMonitoring& ev );

	private:
	
		Socket(const Socket& obj);
		Socket& 			operator=(const Socket& obj);

		const int					_fd;
		const Endpoint				_sockAddr;
		const Endpoint				_entryAddr;
		HttpRequest 				_req;
		HttpResponse 				_resp;
		Buffer						_rxBuffer;
		Buffer						_txBuffer;
		bool						_reset;
		bool						_keepAlive;

		ServerManager&				_sm;
		SocketManager&				_sockm;
		EventMonitoring*			_em;
		HttpHandling				_handler;
};

#endif