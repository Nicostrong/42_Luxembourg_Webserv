/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                    :+:      :+:    :+:   */
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

class Body
{
	public:

		Body( size_t bufferSize );
		~Body( void );

		const std::string&		getTmpFileName( void ) const;

		void					moveBodyFile( const std::string& name );
		void					readInFile( std::vector<char>& receivedTxtBuffer );

		bool					onRead( Buffer& buff, Socket& sock );

		Buffer&					getBuffer( void );
		
	private:
		
		Buffer	 			_buff;
		std::fstream		_fBuff;
		size_t				_size;
		Chunk				_chunk;
		std::string			_fName;

		Body(const Body& obj);
		Body&				operator=( const Body& obj );

		void				openTmpFile( void );
		void				onBodyReceivedTE( Buffer& buff );
		void				onBodyReceivedLength( Buffer& buff, size_t bodyLen );

		size_t				writeInMemory( Buffer& buff, size_t max );
		size_t				writeInFile( Buffer& buff, size_t max );

};

#endif