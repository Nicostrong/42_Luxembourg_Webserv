/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MemoryPool.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:13:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/27 08:49:44 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORYPOOL_HPP
# define MEMORYPOOL_HPP

#include "lib.hpp"
#include "Buffer.hpp"

# define SMALL_BUFF 1024
# define SMALL_AMOUNT 2048
# define MEDIUM_BUFF 8192
# define MEDIUM_AMOUNT 256
# define LARGE_BUFF 16384

# define MAX_CLIENT 1024

class MemoryPool
{
	public:
		class NoAvailableBuffer : public std::exception {
			public:
				const char * what () const throw();
		};
		class InvalidBuffer : public std::exception {
			public:
				const char * what () const throw();
		};
		MemoryPool();
		MemoryPool(const MemoryPool& obj);
		~MemoryPool();
		MemoryPool	operator=(const MemoryPool& obj);
		Buffer*		getSmallBufferFromPool();
		Buffer*		getMediumBufferFromPool();
		Buffer*		getLargeBufferFromPool();
		void 		setAvailableBuffer(Buffer* buff);
	private:
		Buffer*		getBufferFromPool(std::vector<Buffer*>& buffs, 
			std::queue<Buffer*>& available, size_t buffSize);
		
		std::vector<Buffer*>	_smallBuffers;
		std::vector<Buffer*> 	_mediumBuffers;
		std::vector<Buffer*>	_largeBuffers;
		std::queue<Buffer*>		_smallAvailables;
		std::queue<Buffer*>		_mediumAvailables;
		std::queue<Buffer*>		_largeAvailables;
};

# endif