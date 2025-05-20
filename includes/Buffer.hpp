/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:05:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/20 11:14:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_HPP
# define BUFFER_HPP

#include "lib.hpp"

class Buffer
{
    public:
        Buffer(size_t bufferSize);
        Buffer(const Buffer& obj);
        ~Buffer();
        Buffer&						operator=(const Buffer& obj);
		std::vector<char>&			getVector();
		char*						getData();
		char*						getDataUnused();
		char*						getDataUnread();
		size_t						getBufferUsed();
		size_t						getBufferRead();
		size_t						getBufferUnused();
		size_t						getBufferUnread();
		void						setBufferRead(size_t n);
		void						setBufferUsed(size_t n);
		bool						isBufferFull();
		bool						isBufferRead();
		std::vector<char>::iterator	beginUnused();
		void 						reset();
    private:
        std::vector<char>	_buffer;
        size_t				_bufferSize;
		size_t				_bufferUsed;
		size_t				_bufferRead;
};

#endif