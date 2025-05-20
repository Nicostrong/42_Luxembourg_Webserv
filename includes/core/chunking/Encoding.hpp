/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encoding.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:49:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 19:54:24 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODING_HPP
# define ENCODING_HPP

#include "../../lib.hpp"
#include "Chunk.hpp"

class Encoding
{
    public:
        
        
        Encoding();
        Encoding(const Encoding& obj);
        ~Encoding();
        Encoding&       operator=(const Encoding& obj);
        void	        decodeChunked(const std::vector<char>& buffer, 
            size_t bytes);
        void encodeChunk(const std::vector<char>& buf, size_t n);
		const Chunk*	getFrontChunk() const;
		void			popChunk();
        
    private:
        std::string			_rawChunks;
        std::queue<Chunk>	_chunks;

};

#endif
