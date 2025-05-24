/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:43:53 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/24 09:24:41 by fdehan           ###   ########.fr       */
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
			READY = 1,
			MALFORMED = 2,
			TOO_LARGE = 3,
		};
        Headers(MemoryPool& mPool);
        Headers(const Headers& obj);
        ~Headers();
        Headers&		operator=(const Headers& obj);
		Buffer*			getBuffer();
		void			read(int socket);
		void 			parseHeaders();
		void			parseHeader(size_t start, size_t end);
		bool			isHeaderNameValid(size_t nStart, size_t nEnd);
		void			normalizeHeaderName(size_t nStart, size_t nEnd);
		bool			isHeaderPresent(const std::string& name) const;
		const t_string* getHeaderValue(const std::string& name) const;
    private:
		void 	allocateBuff();
		size_t 	getHeaderIndex(const std::string& name) const;

		MemoryPool&				_mPool;
        Buffer*					_buff;
        std::vector<t_string> 	_mapKeys;
		std::vector<t_string> 	_mapValues;
		size_t					_headersEnd;
		State					_state;
};

# endif