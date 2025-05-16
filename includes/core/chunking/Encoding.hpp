/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 11:11:51 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODING_HPP
# define ENCODING_HPP

#include "lib.hpp"
#include "Chunk.hpp"

class Encoding
{
    public:
        
        
        Encoding();
        Encoding(const Encoding& obj);
        ~Encoding();
        Encoding& operator=(const Encoding& obj);
        static std::string encodeChunk(const std::vector<char>& buffer, 
            size_t bytes);
        std::string decodeChunk(const std::vector<char>& buffer, 
            size_t bytes);
        
    private:
        std::string _encodedChunk;
        

};

#endif
