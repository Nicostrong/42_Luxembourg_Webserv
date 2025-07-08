/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiBody.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:55:27 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 11:31:10 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIBODY_HPP
# define CGIBODY_HPP

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../networking/Chunk.hpp"
#include "./../networking/Body.hpp"
#include "./CgiChunk.hpp"

class CgiBody : public Body
{
	public:
		CgiBody( size_t bufferSize );
		~CgiBody();

		bool	onRead( Buffer& buff, Socket& sock );
		void	onBodyReceivedEof( Buffer& buff );
		void	onBodyReceivedTE( Buffer& buff );
	private:
		CgiBody(const CgiBody& obj);
		CgiBody& operator=(const CgiBody& obj);

		CgiChunk _cgiChunk;
};

# endif