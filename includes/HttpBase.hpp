/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/30 16:18:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BASE_HPP
# define HTTP_BASE_HPP

#define ALLOWED_URI_SPECIALS "-_.~:@/?&=#%+[]!$()*,;"
#define ALLOWED_HEADER_VAL "_ :;.,\\/\"'?!(){}[]@<>=-+*#$&`|~^%"


#include "./lib.hpp"
#include "./Buffer.hpp"

class HttpBase
{
	public:
		enum HttpCode
		{
			OK = 200,
			CREATED = 201,
			NO_CONTENT = 204,
			MOVED_PERMANENTLY = 301,
			FOUND = 302,
			BAD_REQUEST = 400,
			FORBIDDEN = 403,
			NOT_FOUND = 404,
			METHOD_NOT_ALLOWED = 405,
			CONFLICT = 409,
			LENGTH_REQUIRED = 411,
			URI_TOO_LONG = 414,
			REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
			INTERNAL_SERVER_ERROR = 500,
			NOT_IMPLEMENTED = 501,
			HTTP_VERSION_NOT_SUPPORTED = 505,
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
		const std::string& 	getHttpVersion() const;
		void 				setHTTP(const std::string html);
		const std::string& 	getRaw() const;
		void 				setRaw(const std::string raw);
		std::string			getHeaders_raw() const;
		bool				isComplete() const;
		void				setAsComplete();
		template <typename T>
		void 				addHeader(const std::string &name, const T& value)
		{
			std::ostringstream oss;

			oss << value;
			this->_headers[name] = oss.str();
		}
		bool				findHeader(const char* name);
		std::string&		findHeaderValue(const char* name);
		const std::map<std::string, std::string>&	getHeaders() const;
		static std::string	getStrStatusCode(HttpCode statusCode);
		static std::string	getDirectoryListing(const std::string &dirPath, 
			const std::string &relativeDir);
	protected:
		HttpBase();
		static bool canBeValidMethod(const std::string& method);
		static bool canBeValidPath(const std::string& path);
		static bool canBeValidHttpProtocol(const std::string& httpVersion);
		static bool isHeaderNameValid(const std::string& name);
		static bool isHeaderValueValid(const std::string& value);
		static std::string normalizeHeaderName(const std::string& name);
		static std::string normalizeUri(const std::string& uri);
		static void 		formatIndividualFile(std::ostringstream& oss, 
			const std::string& filePath, std::string fileName);
		static std::string	formatTime(const time_t& time);
		static std::string	formatTimeHeader(const time_t& time);
		static std::string	truncateString(std::string str, size_t n, 
			size_t truncLen, const std::string& trString);
		static std::string	convertFileSize(off_t size);
		std::string _raw;
		std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;
		HttpCode	_statusCode;
		std::map<std::string, std::string> _headers;
		bool		_transferEncoding;
		bool 		_isComplete;
	private:
};
		

#endif