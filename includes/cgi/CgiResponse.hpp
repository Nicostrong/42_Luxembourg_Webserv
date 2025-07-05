/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/05 09:48:28 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP

#include "./../lib.hpp"
#include "./CgiBody.hpp"
#include "./../http/HttpBase.hpp"

class CgiResponse
{
	public:
		CgiResponse();
		~CgiResponse();

		template <typename T>
		void addHeader(const std::string &name, const T& value)
		{
			std::ostringstream oss;

			oss << value;
			if (HttpBase::normalizeHeaderName(name) == "Set-Cookie")
				this->_cookies.push_back(oss.str());
			else
				this->_headers[name] = oss.str();
		}

		bool										isEof() const;
		bool										isTE()	const;
		bool										isEofReceived() const;
		bool										isProcessFinished() const;
		bool										findHeader(const char* name);
		bool										isError() const;
		size_t										getContentLength() const;
		size_t										getErrorCode() const;
		CgiBody*									getBody();
		std::string&								findHeaderValue(const char* name);
		const std::map<std::string, std::string>&	getHeaders() const;
		const std::list<std::string>&				getCookies() const;
		
		void										setBody(CgiBody* body);
		void										setEof(bool state = true);
		void										setTe(bool state = true);
		void										setEofReceived(bool state = true);
		void										setProcessFinished(bool state = true);
		void										setContentLenght(size_t len);
		void										setCode(size_t code);
		void										setCodeStr(const std::string& codeStr);
		void										setError(bool state = true);
		void										setErrorCode(size_t code);
		void										reset();

    private:
		CgiResponse(const CgiResponse& obj);
		CgiResponse& operator=(const CgiResponse& obj);

		std::map<std::string, std::string>	_headers;
		std::list<std::string>				_cookies;
		CgiBody*							_body;
		size_t								_contentLength;
		size_t								_errorCode;

		bool								_isEofReceived;
		bool								_isProcessFinished;
		bool								_isError;
		bool								_isEof;
		bool								_isTe;
};

#endif