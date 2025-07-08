/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:31:55 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "./HttpBase.hpp"
# include "./HttpRequest.hpp"
# include "./HttpExceptions.hpp"
# include "./../utils/Buffer.hpp"
# include "./../networking/Body.hpp"
# include "./HttpSevereExceptions.hpp"

# define SL_BSIZE	1024

class	Socket;

class	HttpParser
{
	
	public:

		enum State
		{
			HTTP_STARTLINE = 0,
			HTTP_HEADERS = 1,
			HTTP_HEAD_RECEIVED = 2,
			HTTP_BODY = 3,
			HTTP_BODY_RECEIVED = 4,
			HTTP_HANDLED = 5,
		};
		HttpParser();
		HttpParser(const HttpParser& obj);
		virtual					~HttpParser();
		HttpParser&				operator=(const HttpParser& obj);
		void 					onRead(Buffer& buff, Socket& sock);
		
		void 					setState(State state);
		State					getState() const;
		void					reset();

	private:
	
		void					parseStartLine(HttpRequest& req);
		void					parseHeaders(HttpRequest& req);
		void 					parseHeader(const std::string& line, 
			HttpRequest& req);
		bool					handleStartLine(Buffer& buff, HttpRequest& req);
		bool					handleHeaders(Buffer& buff, HttpRequest& req);
		bool					handleBody(Buffer& buff, Socket& sock);

		State 					_state;
		std::string				_slBuffer;
		std::string				_headBuffer;
		std::string				_queryParams;
		
};

# endif