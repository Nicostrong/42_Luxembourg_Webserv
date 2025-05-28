/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 16:59:34 by fdehan           ###   ########.fr       */
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
			CHUNK_LEN = 0,
			CHUNK_TRAILER = 1,
			CHUNK_DATA = 2,
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
        size_t	_received;
        size_t	_len;
		State 	_state;
};

# endif