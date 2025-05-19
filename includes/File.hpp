/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:36:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 13:29:59 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP

#include "lib.hpp"

class File
{
    public:
        File(const std::string& path);
        File(const File& obj);
        ~File();
        File&               operator=(const File& obj);
        bool                getEof() const;
        std::vector<char>   read();
    private:
        std::string     _path;
        bool            _isEof;
        std::ifstream   _fstream;
};

#endif