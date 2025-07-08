/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:34:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODY_HPP
# define BODY_HPP

# include "./../lib.hpp"
# include "./../utils/Buffer.hpp"
# include "./Chunk.hpp"

# define RAM_BUFF	20480
# define TMP_PATH	"/tmp/"
# define MAX_RETRY	3

class	Socket;

class	Body
{
	public:

		Body( size_t bufferSize );
		virtual ~Body( void );

		const std::string&		getTmpFileName( void ) const;

		void					moveBodyFile( const std::string& name );
		void					readInFile( std::vector<char>& receivedTxtBuffer );
		bool					read( Buffer& buff );

		virtual bool			onRead( Buffer& buff, Socket& sock );

		Buffer&					getBuffer( void );
		size_t					getSize()	const;
		std::fstream&			getFstream();
		
	protected:
		
		Buffer	 			_buff;
		std::fstream		_fBuff;
		size_t				_size;
		size_t				_bytesRead;
		Chunk				_chunk;
		std::string			_fName;
		bool				_isReceived;

		Body(const Body& obj);
		Body&				operator=( const Body& obj );

		void				openTmpFile( void );
		virtual void		onBodyReceivedTE( Buffer& buff );
		void				onBodyReceivedLength( Buffer& buff, size_t bodyLen );

		size_t				writeInMemory( Buffer& buff, size_t max );
		size_t				writeInFile( Buffer& buff, size_t max );

};

#endif