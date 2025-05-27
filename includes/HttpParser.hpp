/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/27 09:15:51 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "./HttpBase.hpp"
# include "./core/chunking/Encoding.hpp"
# include "./Buffer.hpp"

# define SL_BSIZE 1024
# define HEAD_BSIZE 8192

class HttpParser : public HttpBase
{
	
	public:
		enum State
		{
			HTTP_STARTLINE = 0,
			HTTP_HEADERS = 1,
			HTTP_BODY = 2,
			HTTP_RECEIVED = 3,
			HTTP_SENT = 4,
			HTTP_INVALID = 5,
			HTTP_SL_TOOBIG = 6,
			HTTP_HEAD_TOOBIG = 7,
		};
		
		HttpParser(const HttpParser& obj);
		virtual					~HttpParser();
		HttpParser&				operator=(const HttpParser& obj);
		void 					parse(Buffer& buff);
		
		State					getState() const;
		Buffer&					getBuffer();
	protected:
		HttpParser();
		
		void					parseStartLine();
		void					parseHeaders();
		void 					parseHeader(const std::string& line);
		
	private:
		State 					_state;
		std::string				_slBuffer;
		std::string				_headBuffer;
		Buffer					_bodyBuffer;
		Encoding				_enc;
		std::string				_queryParams;
		
};

# endif