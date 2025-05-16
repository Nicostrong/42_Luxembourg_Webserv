/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/16 15:39:22 by fdehan           ###   ########.fr       */
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
        std::string		decodeChunked(const std::vector<char>& buffer, 
            size_t bytes);
		const Chunk*	getFrontChunk() const;
		void			popChunk();
        
    private:
        std::string			_encodedChunk;
        std::queue<Chunk>	_receivedChunks;

};

#endif
