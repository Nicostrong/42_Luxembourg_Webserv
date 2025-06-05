/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:26 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:17:53 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHANDLING_HPP
#define RESPONSEHANDLING_HPP

#include "./../lib.hpp"
#include "./../utils/File.hpp"

class Socket;

class ResponseHandling
{
	enum State
	{
		NONE = 0,
		INIT = 1,
		SENT = 2,
	};
    public:
        ResponseHandling();
        ResponseHandling(const ResponseHandling& obj);
        ~ResponseHandling();
        ResponseHandling& operator=(const ResponseHandling& obj);
        void    init(Socket& sock);
		void	send(Socket& sock);
		void	reset();
    private:
        File*	_staticFile;
        State	_state;
};

#endif