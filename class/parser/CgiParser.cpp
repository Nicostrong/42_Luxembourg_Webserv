/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:42 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/11 08:42:15 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parser/CgiParser.hpp"

CgiParser::CgiParser() 
{
    this->_headBuffer.reserve(CGI_HEAD_BUFF);
}

CgiParser::~CgiParser() {}

void	CgiParser::onRead(Buffer &buff)
{
    
}

