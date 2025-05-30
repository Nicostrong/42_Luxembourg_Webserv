/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartLine.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:10:49 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/26 11:35:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTLINE_HPP
# define STARTLINE_HPP

#include "lib.hpp"
#include "Buffer.hpp"
#include "MemoryPool.hpp"

#define START_LINE_READ 1024

class StartLine
{
    public:
		enum State
		{
			RECEIVING = 0,
			READY = 1,
			MALFORMED = 2,
			TOO_LARGE = 3,
		};
		StartLine(MemoryPool& mPool);
		StartLine(const StartLine& obj);
		~StartLine();
		StartLine&	operator=(const StartLine& obj);
		State		getState() const;
		void 		read(int socket);
		void		parseStartLine();
		void		canBeValidMethod(const t_string& str);
		void 		canBeValidUri(const t_string& path);
		void		canBeValidHttpVersion(const t_string& ver);
    private:
		
		void		allocateBuff();

		MemoryPool&				_mPool;
    	Buffer*					_buff;
		State					_state;
		size_t					_startLineEnd;
		std::vector<t_string>	_map;
};

# endif