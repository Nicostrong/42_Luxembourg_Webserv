/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/27 08:52:08 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "./HttpBase.hpp"
# include "./core/chunking/Encoding.hpp"

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
		};
		
		HttpParser(const HttpParser& obj);
		virtual					~HttpParser();
		HttpParser&				operator=(const HttpParser& obj);
		void 					parse(std::vector<char>& buff, size_t n);
		
		State					getState() const;
		Buffer&					getBuffer();
	protected:
		HttpParser();
		
		void					parseStartLine(const std::string& line);
		void 					parseHeader(const std::string& line);
		void					parseHeaders(const std::string& headers);
	private:
		State 					_state;
		std::string				_buffer;
		Buffer					_bodyBuffer;
		Encoding				_enc;
		std::string				_queryParams;
		
};

# endif