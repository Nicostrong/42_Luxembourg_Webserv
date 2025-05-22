/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MemoryPool.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:13:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/22 18:47:47 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORYPOOL_HPP
# define MEMORYPOOL_HPP

#include "lib.hpp"
#include "Buffer.hpp"

# define DHEAD_BUFF 1024
# define DBIG_HEAD_BUFF 8192
# define DHEAD_BIG_BUFF_N 4
# define MAX_CLIENT 1024

class MemoryPool
{
	public:
		enum Type
		{
			SMALL = 0,
			BIG = 1,	
		};
		MemoryPool();
		MemoryPool(const MemoryPool& obj);
		~MemoryPool();
		MemoryPool operator=(const MemoryPool& obj);
	private:
		std::vector<Buffer*>	_smallBuffers;
		std::vector<Buffer*> 	_bigBuffers;
		std::queue<Buffer*>		_smallAvailables;
		std::queue<Buffer*>		_bigAvailables;
		size_t					_small;
};

# endif