/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 09:54:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODING_HPP
# define ENCODING_HPP

#include "lib.hpp"

class Encoding
{
    public:
        enum States
        {
            CHUNK_LEN = 0,
            CHUNK_EXT = 1,
            CHUNK_DATA = 2,
            CHUNK_END = 3,
            CHUNK_ERROR = 4,
        };
        
        Encoding();
        Encoding(const Encoding& obj);
        ~Encoding();
        Encoding& operator=(const Encoding& obj);
        static std::string encodeChunk(const std::vector<char>& buffer, 
            size_t bytes);
        std::string decodeChunk(const std::vector<char>& buffer, 
            size_t bytes);
        
    private:
        static size_t convertHexa(const std::string& str);
        std::string _encodedChunk;
        States      _state;
        size_t      _chunkLen;
};

#endif
