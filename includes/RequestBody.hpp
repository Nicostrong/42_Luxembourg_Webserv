/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 20:31:11 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBODY_HPP
# define REQUESTBODY_HPP

#include "Buffer.hpp"
#include "Chunk.hpp"
#include "lib.hpp"

#define RAM_BUFF 20480
#define TMP_PATH "/tmp/"

class RequestBody
{
	public:
		RequestBody();
		~RequestBody();
		void			add(Buffer& buff);
	private:
		RequestBody(const RequestBody& obj);
		RequestBody&	operator=(const RequestBody& obj);
		void			openTmpFile();
		
		Buffer	 		_buff;
		std::fstream	_fBuff;
		size_t			_size;
		Chunk			_chunk;
		std::string		_fName;
};

#endif