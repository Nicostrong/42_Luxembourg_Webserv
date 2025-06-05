/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:36:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:36:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/File.hpp"

File::File(const std::string& path) : _path(path)
{
    this->_fstream.open(path.c_str());
    if (!this->_fstream || !this->_fstream.is_open()) 
		throw std::runtime_error("Failed to open file");
}

File::File(const File& obj) : _path(obj._path)
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
    return (this->_fstream.eof());
}

void File::read(Buffer& buff, size_t n)
{
    if (buff.isBufferFull())
        return ;
    size_t readSize = n < buff.getBufferUnused() ? n : buff.getBufferUnused();
    this->_fstream.read(buff.getDataUnused(), readSize);
   
    if (!this->_fstream && !this->_fstream.eof())
        throw std::runtime_error("Read failed");

    buff.setBufferUsed(this->_fstream.gcount());
}
