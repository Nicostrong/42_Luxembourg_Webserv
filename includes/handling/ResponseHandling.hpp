/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:26 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:30:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHANDLING_HPP
# define RESPONSEHANDLING_HPP

# include "./../lib.hpp"
# include "./../utils/File.hpp"

class   Socket;

class   ResponseHandling
{
    public:

        enum State
        {
            NONE = 0,
            INIT = 1,
            SENT = 2,
        };
        ResponseHandling();
        ResponseHandling(const ResponseHandling& obj);
        ~ResponseHandling();
        ResponseHandling& operator=(const ResponseHandling& obj);

        State   getState() const;
        void    init(Socket& sock);
		void	send(Socket& sock);
		void	reset();

    private:

        File*	_staticFile;
        State	_state;
        
};

#endif