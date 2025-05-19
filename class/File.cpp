/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:36:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 13:55:29 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/File.hpp"

File::File(const std::string& path) : _path(path), _isEof(false)
{
    this->_fstream.open(path.c_str());
    if (!this->_fstream || !this->_fstream.is_open()) 
		throw std::runtime_error("Failed to open file");
}

File::File(const File& obj) : _path(obj._path), _isEof(false)
{
    this->_fstream.open(this->_path.c_str());
     if (!this->_fstream || !this->_fstream.is_open()) 
        throw std::runtime_error("Failed to open file");
}

File::~File() 
{
    this->_fstream.close();
}

File& File::operator=(const File& obj) 
{
    (void)obj;
    return (*this);
}

bool File::getEof() const
{
    return (this->_isEof);
}

std::vector<char> File::read()
{
    std::vector<char> buf;

    buf.reserve(READ_BUFFER_SIZE);
    
    this->_fstream.read(buf.data(), READ_BUFFER_SIZE);
    std::streamsize count = this->_fstream.gcount();

    if (!this->_fstream && !this->_fstream.eof())
        throw std::runtime_error("Read failed");
    this->_isEof = this->_fstream.eof();
    buf.resize(count); 
    return (buf);
}
