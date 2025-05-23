/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:43:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/23 10:54:11 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_HPP
# define HEADERS_HPP

#include "lib.hpp"
#include "MemoryPool.hpp"

# define HEAD_MAX_READ 1024

class Headers
{
    public:
		enum State
		{
			RECEIVING = 0,
			HANDLING = 1,
			READY = 2,
			MALFORMED = 3,
			TOO_LARGE = 4,
		};
        Headers(MemoryPool& mPool);
        Headers(const Headers& obj);
        ~Headers();
        Headers&	operator=(const Headers& obj);
		Buffer*		getBuffer();
		void		read(int socket);
		void		isHeadersReceived();
    private:
        struct t_string 
        {
            size_t pos;
            size_t len;
        };

		void allocateBuff();

		MemoryPool&				_mPool;
        Buffer*					_buff;
        std::vector<t_string> 	_mapKeys;
		std::vector<t_string> 	_mapValues;
		size_t					_headersEnd;
		State					_state;
};

# endif