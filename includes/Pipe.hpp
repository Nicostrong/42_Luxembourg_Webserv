/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:47:38 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/20 23:02:06 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_HPP
# define PIPE_HPP

#include "lib.hpp"

class Pipe
{
    public:
		Pipe();
		~Pipe();
		int	getIn() const;
		int	getOut() const;
		void closeIn();
		void closeOut();
    private:
		Pipe(const Pipe& obj);
		Pipe& operator=(const Pipe& obj);
		int	_pipeIn;
		int	_pipeOut;
};

#endif