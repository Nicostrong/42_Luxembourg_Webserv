/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/06 21:25:56 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BASE_HPP
# define HTTP_BASE_HPP

#define ALLOWED_URI_SPECIALS "-_.~:@/?&=#%+[]!$()*,;"
#define ALLOWED_HEADER_VAL "_ :;.,\\/\"'?!(){}[]@<>=-+*#$&`|~^%"
#define CRLF "\r\n"

#include "lib.hpp"

class HttpBase
{
	public:
		enum HttpCode
		{
			OK = 200,
			BAD_REQUEST = 400,
			NOT_FOUND = 404,
			INTERNAL_SERVER_ERROR = 500,
		};
		
		HttpBase(const HttpBase& obj);
		virtual 			~HttpBase();
		HttpBase&			operator=(const HttpBase& obj);
		HttpCode			getStatusCode() const;
		void				setStatusCode(HttpBase::HttpCode status);
		const std::string&	getMethod() const;
		void				setMethod(std::string method);
		const std::string&	getUri() const;
		void				setUri(std::string uri);
		const std::string& 	getBody() const;
		void 				setBody(const std::string body);
		const std::string& 	getHTTP() const;
		void 				setHTTP(const std::string html);
		const std::string& 	getRaw() const;
		void 				setRaw(const std::string raw);
		std::string 	getHeaders_raw() const;
		const std::map<std::string, std::string>&	getHeaders() const;
		static std::string	getStrStatusCode(HttpCode statusCode);
		static std::string  getDefaultErrorPage(HttpCode statusCode);
	protected:
		HttpBase();
		static bool canBeValidMethod(std::string& method);
		static bool canBeValidPath(std::string& path);
		static bool canBeValidHttpProtocol(std::string& httpVersion);
		static bool isHeaderNameValid(std::string& name);
		static bool isHeaderValueValid(std::string& value);
		static std::string normalizeHeaderName(std::string& name);
		std::string _raw;
		std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;
		HttpCode	_statusCode;
		std::map<std::string, std::string> _headers;
};

#endif