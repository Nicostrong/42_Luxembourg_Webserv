/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:26:16 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBODY_HPP
# define REQUESTBODY_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./Chunk.hpp"

#define RAM_BUFF 20480
#define TMP_PATH "/tmp/"
#define MAX_RETRY 3

class Socket;

class BodyParser
{
	public:
		BodyParser(size_t bufferSize);
		~BodyParser();
		const std::string&		getTmpFileName() const;
		void					moveBodyFile(const std::string& name);
		bool 					onBodyReceived(Buffer& buff, Socket& sock);
		
	private:
		BodyParser(const BodyParser& obj);
		BodyParser&			operator=(const BodyParser& obj);
		void					onBodyReceivedLength(Buffer& buff, size_t bodyLen);
		void 					onBodyReceivedTE(Buffer& buff);
		size_t					writeInMemory(Buffer& buff, size_t max);
		size_t					writeInFile(Buffer& buff, size_t max);
		void					readInFile(std::vector<char>& receivedTxtBuffer);
		void					openTmpFile();
		
		Buffer	 		_buff;
		std::fstream	_fBuff;
		size_t			_size;
		Chunk			_chunk;
		std::string		_fName;
};

#endif