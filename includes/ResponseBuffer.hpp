/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:14:37 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 15:54:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEBUFFER_HPP
# define RESPONSEBUFFER_HPP

#include "lib.hpp"

class Socket;

class ResponseBuffer
{
    public:
        ResponseBuffer(Socket& ctx);
        ResponseBuffer(const ResponseBuffer& obj);
		ResponseBuffer(const ResponseBuffer& obj, Socket& ctx);
        ~ResponseBuffer();
        ResponseBuffer& operator=(const ResponseBuffer& obj);
		size_t			getFlushCount() const;
		void    		bufferize(const std::vector<char>& buff, size_t n);
        void            flush();
		void			clear();
		void			reset();
    private:
        Socket*				_ctx;
        std::vector<char>	_buff;
        size_t				_pos;
		size_t				_flushCount;
};

#endif