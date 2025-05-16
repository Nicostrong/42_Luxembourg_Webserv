/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:56:59 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 11:11:53 by fdehan           ###   ########.fr       */
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
            CHUNK_END = 3,
            CHUNK_ERROR = 4,
            CHUNK_COMPLETE = 5,
        };
        Chunk();
        Chunk(const Chunk& obj);
        ~Chunk();
        Chunk&	operator=(const Chunk& obj);
		void	decodeChunk(std::string& data);
    private:
		static size_t convertHexa(const std::string& str);
		
        State		_state;
        size_t		_len;
        std::string	_data;
};

#endif