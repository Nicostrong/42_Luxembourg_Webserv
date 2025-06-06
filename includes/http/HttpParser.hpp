/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:57:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "./../utils/Buffer.hpp"
# include "./../networking/BodyParser.hpp"
# include "./HttpBase.hpp"
# include "./HttpExceptions.hpp"

# define SL_BSIZE 1024
# define HEAD_BSIZE 8192

class Socket;

class HttpParser : public HttpBase
{
	
	public:
		enum State
		{
			HTTP_STARTLINE = 0,
			HTTP_HEADERS = 1,
			HTTP_HEAD_HANDLING = 2,
			HTTP_BODY = 3,
			HTTP_BODY_HANDLING = 4,
			HTTP_RECEIVED = 5,
			HTTP_SENT = 6
		};
		
		HttpParser(const HttpParser& obj);
		virtual					~HttpParser();
		HttpParser&				operator=(const HttpParser& obj);
		void 					onRequest(Buffer& buff, Socket& sock);
		
		void 					setState(State state);
		State					getState() const;
		BodyParser*			getBody() const;
	protected:
		HttpParser();
		
		void					parseStartLine();
		void					parseHeaders();
		void 					parseHeader(const std::string& line);
		bool					handleStartLine(Buffer& buff);
		bool					handleHeaders(Buffer& buff);
		bool					handleBody(Buffer& buff, Socket& sock);
		
	private:
		State 					_state;
		std::string				_slBuffer;
		std::string				_headBuffer;
		std::string				_queryParams;
		BodyParser*			_reqBody;
		
};

# endif