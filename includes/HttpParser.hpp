/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 16:20:33 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "HttpBase.hpp"
# include "core/chunking/Encoding.hpp"

class HttpParser : public HttpBase
{
	
	public:
		class SocketReadException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		HttpParser(const HttpParser& obj);
		virtual ~HttpParser();
		HttpParser& operator=(const HttpParser& obj);
	protected:
		HttpParser();
		void 					parse();
		void					parseStartLine(std::string &line);
		void 					parseHeader(std::string &line);
	private:
		Encoding				_enc;
		size_t					_pos;
		std::string				_queryParams;
		
};

# endif