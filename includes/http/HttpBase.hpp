/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 16:08:34 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BASE_HPP
# define HTTP_BASE_HPP

#define ALLOWED_URI_SPECIALS "-_.~:@/?&=#%+[]!$()*,;"
#define ALLOWED_HEADER_VAL "_ :;.,\\/\"'?!(){}[]@<>=-+*#$&`|~^%"


#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"

class HttpBase
{
	public:
		enum HttpCode
		{
			CONTINUE = 100,
			SWITCHING_PROTOCOLS = 101,
			PROCESSING = 102,
			EARLY_HINTS = 103,
			OK = 200,
			CREATED = 201,
			ACCEPTED = 202,
			NON_AUTHORITATIVE_INFORMATION = 203,
			NO_CONTENT = 204,
			RESET_CONTENT = 205,
			PARTIAL_CONTENT = 206,
			MULTI_STATUS = 207,
			ALREADY_REPORTED = 208,
			IM_USED = 226,
			MULTIPLE_CHOICES = 300,
			MOVED_PERMANENTLY = 301,
			FOUND = 302,
			SEE_OTHER = 303,
			NOT_MODIFIED = 304,
			USE_PROXY = 305,
			TEMPORARY_REDIRECT = 307,
			PERMANENT_REDIRECT = 308,
			BAD_REQUEST = 400,
			UNAUTHORIZED = 401,
			PAYMENT_REQUIRED = 402,
			FORBIDDEN = 403,
			NOT_FOUND = 404,
			METHOD_NOT_ALLOWED = 405,
			NOT_ACCEPTABLE = 406,
			PROXY_AUTHENTICATION_REQUIRED = 407,
			REQUEST_TIMEOUT = 408,
			CONFLICT = 409,
			GONE = 410,
			LENGTH_REQUIRED = 411,
			PRECONDITION_FAILED = 412,
			PAYLOAD_TOO_LARGE = 413,
			URI_TOO_LONG = 414,
			UNSUPPORTED_MEDIA_TYPE = 415,
			RANGE_NOT_SATISFIABLE = 416,
			EXPECTATION_FAILED = 417,
			IM_A_TEAPOT = 418,
			MISDIRECTED_REQUEST = 421,
			UNPROCESSABLE_ENTITY = 422,
			LOCKED = 423,
			FAILED_DEPENDENCY = 424,
			TOO_EARLY = 425,
			UPGRADE_REQUIRED = 426,
			PRECONDITION_REQUIRED = 428,
			TOO_MANY_REQUESTS = 429,
			REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
			UNAVAILABLE_FOR_LEGAL_REASONS = 451,
			INTERNAL_SERVER_ERROR = 500,
			NOT_IMPLEMENTED = 501,
			BAD_GATEWAY = 502,
			SERVICE_UNAVAILABLE = 503,
			GATEWAY_TIMEOUT = 504,
			HTTP_VERSION_NOT_SUPPORTED = 505,
			VARIANT_ALSO_NEGOTIATES = 506,
			INSUFFICIENT_STORAGE = 507,
			LOOP_DETECTED = 508,
			NOT_EXTENDED = 510,
			NETWORK_AUTHENTICATION_REQUIRED = 511
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
		const std::string& 	getRawBody() const;
		void 				setRawBody(const std::string body);
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
		static bool canBeValidMethod(const std::string& method);
		static bool canBeValidPath(const std::string& path);
		static bool canBeValidHttpProtocol(const std::string& httpVersion);
		static bool isHeaderNameValid(const std::string& name);
		static bool isHeaderValueValid(const std::string& value);
		static std::string normalizeHeaderName(const std::string& name);
		static std::string normalizeUri(const std::string& uri);
	protected:
		HttpBase();
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