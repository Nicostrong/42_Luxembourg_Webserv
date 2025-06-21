/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHandling.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:59:34 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/21 09:50:48 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHANDLING_HPP
# define HTTPHANDLING_HPP

# include "../lib.hpp"
# include "HttpParser.hpp"
# include "HttpExceptions.hpp"
# include "../cgi/CgiParser.hpp"
# include "../handling/MyCGI.hpp"
# include "../cgi/CgiResponse.hpp"
# include "HttpSevereExceptions.hpp"
# include "../events/EventMonitoring.hpp"
# include "../cgi/CgiResponseHandling.hpp"
# include "../handling/RequestHandling.hpp"
# include "../handling/ResponseHandling.hpp"

class	Socket;

class	HttpHandling
{
	public:

		HttpHandling( void );
		~HttpHandling( void );

		/*	METHODS	*/
		void			onRead( EventMonitoring& em, Socket* sock );
		void			onWrite( EventMonitoring& em, Socket* sock );
		void			onTick(EventMonitoring& em, Socket* sock);
		void			setBodyRequired( void );
		void			reset( void );
		CgiParser&		getCgiParser();
		CgiResponse&	getCgiResponse();
		ResponseHandling& getResponseHandling();

		/*	SETTER	*/
		void		setCGI( Socket& socket );

		/*	GETTER	*/
		MyCGI*		getCGI( void );
		
	private:
		HttpHandling(HttpHandling& obj);
		HttpHandling operator=(const HttpHandling& obj);

		void		setConnectionClose(Socket& sock);
		
		HttpParser			_parser;
		CgiParser			_cgiParser;
		ResponseHandling	_resHandling;
		CgiResponse			_cgiResp;
		MyCGI*				_cgi;
};

#endif