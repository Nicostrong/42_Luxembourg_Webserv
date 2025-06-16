/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/16 21:32:45 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSE_HPP
# define CGIRESPONSE_HPP

#include "./../lib.hpp"

class CgiResponse
{
    public:
        CgiResponse();
        CgiResponse(const CgiResponse& obj);
        ~CgiResponse();
        CgiResponse& operator=(const CgiResponse& obj);

        template <typename T>
        void addHeader(const std::string &name, const T& value)
		{
			std::ostringstream oss;

			oss << value;
			this->_headers[name] = oss.str();
		}
        
		bool				                        findHeader(const char* name);
		std::string&		                        findHeaderValue(const char* name);
        const std::map<std::string, std::string>&   getHeaders() const;
    private:
        std::map<std::string, std::string> _headers;
};

#endif