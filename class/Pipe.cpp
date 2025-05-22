/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:53:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/22 13:35:39 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pipe.hpp"

Pipe::Pipe() : _pipeIn(-1), _pipeOut(-1)
{
    int p[2];
    
    if (pipe(p) == -1)
        throw std::runtime_error("Pipes failed");
    this->_pipeIn = p[1];
    this->_pipeOut = p[0];
}

Pipe::~Pipe()
{
    if (this->_pipeIn > 2)
        close(this->_pipeIn);
    if (this->_pipeOut > 2)
        close(this->_pipeOut);
}

int	Pipe::getIn() const
{
    return (this->_pipeIn);    
}

int	Pipe::getOut() const
{
    return (this->_pipeOut);
}

void Pipe::closeIn()
{
    if (this->_pipeIn > 2)
        close(this->_pipeIn);
    this->_pipeIn = -1; 
}

void Pipe::closeOut()
{
    if (this->_pipeOut > 2)
        close(this->_pipeOut);
    this->_pipeOut = -1; 
}