/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:56:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/17 11:42:52 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSER_HPP
# define HTTPPARSER_HPP

# include "./HttpBase.hpp"
# include "./core/chunking/Encoding.hpp"

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