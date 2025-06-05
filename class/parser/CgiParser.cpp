/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 10:52:44 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parser/CgiParser.hpp"

CgiParser::CgiParser() 
{
    this->_headBuffer.reserve(CGI_HEAD_BUFF);
}

void	CgiParser::onData(Buffer &buff)
{
    
}

CgiParser::~CgiParser() {}