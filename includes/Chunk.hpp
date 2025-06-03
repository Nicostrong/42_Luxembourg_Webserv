/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 10:00:17 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

#include "Buffer.hpp"
#include "lib.hpp"
#include "HttpExceptions.hpp"
#include "HttpBase.hpp"
#include "HttpSevereExceptions.hpp"

class Chunk
{
    public:
		enum State
		{
            CHUNK_START = 0,
			CHUNK_HEAD = 1,
			CHUNK_DATA = 2,
            CHUNK_END = 3,
		};
        Chunk();
        Chunk(size_t len);
        Chunk(const Chunk& obj);
        ~Chunk();
        Chunk& operator=(const Chunk& obj);
        void    setReceived(size_t received);
        size_t  getReceived() const;
        size_t  getLen() const;
        State   getState() const;
		size_t	handleChunk(Buffer& buff);
    private:
        void    handleChunkHead(Buffer& buff);
        size_t  handleChunkData(Buffer& buff);
        size_t  convertHexa(const std::string& str);
        
        size_t	_received;
        size_t	_len;
		State 	_state;
};

# endif