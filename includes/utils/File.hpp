/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:36:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:00:10 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP

#include "./../lib.hpp"
#include "./Buffer.hpp"

class File
{
    public:
        File(const std::string& path);
        File(const File& obj);
        ~File();
        File&				operator=(const File& obj);
        bool				getEof() const;
        void				read(Buffer& buff, size_t n);
    private:
        std::string     _path;
        std::ifstream   _fstream;
};

#endif