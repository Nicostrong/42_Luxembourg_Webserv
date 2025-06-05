/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:00:57 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 10:04:31 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
# define CGIPARSER_HPP

#include "./../lib.hpp"

#define CGI_HEAD_BUFF 8192

class CgiParser
{
    public:
        CgiParser();
        ~CgiParser();
    private:
        CgiParser(const CgiParser& obj);
        CgiParser& operator=(const CgiParser& obj);

        std::string _headBuffer;
};

# endif