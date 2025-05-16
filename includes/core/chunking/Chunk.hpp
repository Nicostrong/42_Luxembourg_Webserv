/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:56:59 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 15:33:11 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "lib.hpp"

class Chunk
{
    public:
        enum State
        {
            CHUNK_LEN = 0,
            CHUNK_EXT = 1,
            CHUNK_DATA = 2,
            CHUNK_REICEIVED = 3,
            CHUNK_SENT = 4,
        };
        Chunk();
        Chunk(const std::vector<char>& buffer, size_t bytes);
        Chunk(const Chunk& obj);
        ~Chunk();
        Chunk&	operator=(const Chunk& obj);
		void	decodeChunk(std::string& data);
        void    encodeChunk();
        State   getState() const;
    private:
		static size_t convertHexa(const std::string& str);
		
        State		_state;
        size_t		_len;
        std::string	_data;
        std::string _encoded;
};

#endif