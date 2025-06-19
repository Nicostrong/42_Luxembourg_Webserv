/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:34 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 15:31:00 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLING_HPP
# define HTTPHANDLING_HPP

# include "../lib.hpp"
# include "HttpParser.hpp"
# include "HttpExceptions.hpp"
# include "../handling/CGI.hpp"
# include "HttpSevereExceptions.hpp"
# include "../events/EventMonitoring.hpp"
# include "../cgi/CgiParser.hpp"
# include "../cgi/CgiResponseHandling.hpp"
# include "../cgi/CgiResponse.hpp"
# include "../handling/RequestHandling.hpp"
# include "../handling/ResponseHandling.hpp"

class	Socket;

class	HttpHandling
{
	public:

		HttpHandling( void );
		~HttpHandling( void );

		/*	METHODS	*/
		void	onRead( EventMonitoring& em, Socket* sock );
		void	onWrite( EventMonitoring& em, Socket* sock );
		void	setBodyRequired( void );
		void	reset( void );

		/*	SETTER	*/
		void	setCGI( Socket& socket );

		/*	GETTER	*/
		MyCGI*	getCGI( void );
		
	private:
		HttpHandling(HttpHandling& obj);
		HttpHandling operator=(const HttpHandling& obj);

		void	setConnectionClose(Socket& sock);
		
		HttpParser			_parser;
		CgiParser			_cgiHandler;
		ResponseHandling	_resHandling;
		CgiResponse			_cgiResp;
		MyCGI*				_cgi;
};

#endif