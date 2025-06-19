/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:23:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP

#include "./../lib.hpp"
#include "./../networking/Body.hpp"

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
		void										reset();

    private:
		CgiResponse(const CgiResponse& obj);
		CgiResponse& operator=(const CgiResponse& obj);

		size_t								_code;
		std::string 						_strCode;
		std::map<std::string, std::string>	_headers;
		Body*								_body;
};

#endif