/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/04 16:37:44 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../http/HttpExceptions.hpp"
#include "./../http/HttpBase.hpp"
#include "./../http/HttpSevereExceptions.hpp"

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
        Chunk&          operator=(const Chunk& obj);
        void            setReceived(size_t received);
        size_t          getReceived() const;
        size_t          getLen() const;
        State           getState() const;
		size_t	        handleChunk(Buffer& buff);
        static bool     isHexaValid(const std::string& hex);
    private:
        void    handleChunkHead(Buffer& buff);
        size_t  handleChunkData(Buffer& buff);
        size_t  convertHexa(const std::string& str);
        
        size_t	_received;
        size_t	_len;
		State 	_state;
};

# endif