/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:35:11 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

# include "./../lib.hpp"
# include "./../utils/Buffer.hpp"
# include "./../http/HttpBase.hpp"
# include "./../http/HttpExceptions.hpp"
# include "./../http/HttpSevereExceptions.hpp"

class	Chunk
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
		Chunk(size_t limit);
		Chunk(const Chunk& obj);
		~Chunk();
		Chunk&			operator=(const Chunk& obj);
		State			getState() const;
		size_t			handleChunk(Buffer& buff);
		static bool		isHexaValid(const std::string& hex);

	private:

		void	handleChunkStart();
		void	handleChunkHead(Buffer& buff);
		size_t	handleChunkData(Buffer& buff);
		size_t	convertHexa(const std::string& str);
		
		size_t	_bytesReceived;
		size_t	_chunkSize;
		size_t	_chunksReceived;
		size_t	_bodySize;
		size_t	_bodyLimit;
		State	_state;
		
};

# endif