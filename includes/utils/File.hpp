/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:36:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:41:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP

# include "../lib.hpp"
# include "./Buffer.hpp"

class   File
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