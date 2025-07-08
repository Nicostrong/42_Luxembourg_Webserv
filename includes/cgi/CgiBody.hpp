/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiBody.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:55:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:25:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIBODY_HPP
# define CGIBODY_HPP

# include "./../lib.hpp"
# include "./CgiChunk.hpp"
# include "./../utils/Buffer.hpp"
# include "./../networking/Body.hpp"
# include "./../networking/Chunk.hpp"

class	CgiBody : public	Body
{
	public:

		CgiBody( size_t bufferSize );
		~CgiBody( void );

		bool	onRead( Buffer& buff, Socket& sock );
		void	onBodyReceivedEof( Buffer& buff );
		void	onBodyReceivedTE( Buffer& buff );

	private:
	
		CgiBody(const CgiBody& obj);
		CgiBody& operator=(const CgiBody& obj);

		CgiChunk _cgiChunk;
		
};

# endif