/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 15:08:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP

#include "./../lib.hpp"
#include "./CgiBody.hpp"

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
			this->_headers[name] = oss.str();
		}
 
		void										setCode(size_t code);
		void										setCodeStr(const std::string& codeStr);
		bool				                        findHeader(const char* name);
		std::string&		                        findHeaderValue(const char* name);
        const std::map<std::string, std::string>&   getHeaders() const;
		CgiBody*									getBody();
		void										reset();


		bool										isEof() const;
		bool										isTe()	const;
		size_t										getContentLenght() const;
		bool										isEofReceived() const;
		bool										isProcessFinished() const;
		void										setBody(CgiBody* body);
		void										setEof(bool state = true);
		void										setTe(bool state = true);
		void										setContentLenght(size_t len);
		void										setEofReceived(bool state = true);
		void										setProcessFinished(bool state = true);

    private:
		CgiResponse(const CgiResponse& obj);
		CgiResponse& operator=(const CgiResponse& obj);

		size_t								_code;
		std::string 						_strCode;
		std::map<std::string, std::string>	_headers;
		CgiBody*							_body;

		bool								_isEof;
		bool								_isTe;
		size_t								_contentLength;

		bool								_isEofReceived;
		bool								_isProcessFinished;
};

#endif