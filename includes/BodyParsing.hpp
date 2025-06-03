/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 09:15:42 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBODY_HPP
# define REQUESTBODY_HPP

#include "Buffer.hpp"
#include "Chunk.hpp"
#include "lib.hpp"

#define RAM_BUFF 20480
#define TMP_PATH "/tmp/"
#define MAX_RETRY 3

class Socket;

class BodyParsing
{
	public:
		BodyParsing(size_t bufferSize);
		~BodyParsing();
		const std::string&		getTmpFileName() const;
		void					moveBodyFile(const std::string& name);
		bool 					onBodyReceived(Buffer& buff, Socket& sock);
		
	private:
		BodyParsing(const BodyParsing& obj);
		BodyParsing&			operator=(const BodyParsing& obj);
		void					onBodyReceivedLength(Buffer& buff, size_t bodyLen);
		void 					onBodyReceivedTE(Buffer& buff);
		size_t					writeInMemory(Buffer& buff, size_t max);
		size_t					writeInFile(Buffer& buff, size_t max);
		void					openTmpFile();
		
		Buffer	 		_buff;
		std::fstream	_fBuff;
		size_t			_size;
		Chunk			_chunk;
		std::string		_fName;
};

#endif