/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiCgiChunk.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:28:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 11:21:11 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGICHUNK_HPP
# define CGICHUNK_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../http/HttpExceptions.hpp"
#include "./../http/HttpBase.hpp"
#include "./../http/HttpSevereExceptions.hpp"

class CgiChunk
{
	public:
		enum State
		{
			CHUNK_START = 0,
			CHUNK_HEAD = 1,
			CHUNK_DATA = 2,
			CHUNK_END = 3,
		};
		
		CgiChunk();
		CgiChunk(size_t limit);
		CgiChunk(const CgiChunk& obj);
		~CgiChunk();
		CgiChunk&		operator=(const CgiChunk& obj);
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
		State	_state;
};

# endif