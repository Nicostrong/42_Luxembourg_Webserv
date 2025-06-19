/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:00:57 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/16 18:49:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
# define CGIPARSER_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../http/HttpExceptions.hpp"
#include "./../http/HttpBase.hpp"
#include "./CgiResponse.hpp"

#define CGI_HEAD_BUFF 8192

class CgiParser
{
    public:
        enum State
        {
			CGI_HEAD = 0,
			CGI_HEAD_RECEIVED = 1,
			BODY_RECEIVING = 2,
			ERROR = 2,
        };
        CgiParser();
        ~CgiParser();
		
		void	onRead(Buffer &buff, CgiResponse& cgiResponse);
        void	parseHeaders(CgiResponse& cgiResponse);
		void	parseHeader(const std::string& line, CgiResponse& cgiResponse);
		bool	handleHeaders(Buffer& buff, CgiResponse& cgiResponse);
    private:
        CgiParser(const CgiParser& obj);
        CgiParser& operator=(const CgiParser& obj);

        std::string _headBuffer;
		State		_state;
};

# endif