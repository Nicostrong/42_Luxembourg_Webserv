/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:09:29 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:37:16 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "./../lib.hpp"
# include "./../utils/Ip.hpp"
# include "./../utils/File.hpp"
# include "./../utils/Buffer.hpp"
# include "./../utils/Endpoint.hpp"
# include "./../http/HttpRequest.hpp"
# include "./../http/HttpResponse.hpp"
# include "./../http/HttpHandling.hpp"
# include "./../http/HttpExceptions.hpp"
# include "./../events/IEventHandler.hpp"
# include "./../server/ServerManager.hpp"
# include "./../events/EventMonitoring.hpp"
# include "./../http/HttpSevereExceptions.hpp"
# include "./../handling/ResponseHandling.hpp"

# define RX_SIZE	1024

class	SocketManager;

class	Socket : public	IEventHandler
{
	public:
	
		Socket( int fd, const Endpoint& sockAddr, const Endpoint& entryAddr,
				ServerManager& sm, SocketManager& sockm );
		~Socket( void );
		
		bool 				operator==( const Socket& obj );
		int					getSocket( void ) const;
		const Endpoint&		getSockAddr( void ) const;
		const Endpoint&		getEntryAddr( void ) const;
		HttpRequest&		getReq( void );
		HttpResponse&		getResp( void );
		Buffer&				getRxBuffer( void );
		Buffer&				getTxBuffer( void );
		ServerManager&		getSM( void );
		SocketManager&		getSockM();
		EventMonitoring&	getEM( void );
		HttpHandling&		getHandler();
		bool				getDataSent() const;
		void 				setSocketClose();
		void				setReset();
		void				setEM( EventMonitoring& em );
		void				reset(EventMonitoring& em);
		void				onReadEvent(int fd, EventMonitoring& em);
		void				onWriteEvent(int fd, EventMonitoring& em);
		void				onCloseEvent(int fd, EventMonitoring& em);
		void				onTickEvent(int fd, EventMonitoring& em);

	private:
	
		Socket( const Socket& obj );
		Socket& 			operator=( const Socket& obj );

		void				setError(HttpBase::HttpCode code, EventMonitoring& em);

		const int			_fd;
		const Endpoint		_sockAddr;
		const Endpoint		_entryAddr;
		HttpRequest 		_req;
		HttpResponse 		_resp;
		Buffer				_rxBuffer;
		Buffer				_txBuffer;
		bool				_reset;
		bool				_keepAlive;
		bool				_isDataSent;
		HttpHandling		_handler;
		ServerManager&		_sm;
		SocketManager&		_sockm;
		EventMonitoring*	_em;

};

#endif