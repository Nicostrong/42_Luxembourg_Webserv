/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:00:57 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 10:41:08 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
# define CGIPARSER_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"

#define CGI_HEAD_BUFF 8192

class CgiParser
{
    public:
        enum State
        {
			HEAD_RECEVING = 0,
			BODY_RECEIVING = 1,
			ERROR = 2,
        };
        CgiParser();
        ~CgiParser();
		void	onData(Buffer &buff);
    private:
        CgiParser(const CgiParser& obj);
        CgiParser& operator=(const CgiParser& obj);

        std::string _headBuffer;
};

# endif