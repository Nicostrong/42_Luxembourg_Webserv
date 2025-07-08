/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:47:38 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:42:00 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_HPP
# define PIPE_HPP

# include "../lib.hpp"

class	Pipe
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