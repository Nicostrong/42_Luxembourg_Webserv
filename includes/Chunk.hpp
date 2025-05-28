/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 20:53:05 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

#include "Buffer.hpp"
#include "lib.hpp"

class Chunk
{
    public:
		enum State
		{
			CHUNK_HEAD = 0,
			CHUNK_DATA = 1,
		};
        Chunk();
        Chunk(size_t len);
        Chunk(const Chunk& obj);
        ~Chunk();
        Chunk& operator=(const Chunk& obj);
        void    setReceived(size_t received);
        size_t  getReceived() const;
        size_t  getLen() const;
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