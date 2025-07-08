/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fd.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 08:36:55 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:40:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_HPP
# define FD_HPP

#include "../lib.hpp"

class	Fd
{
    public:

		static void setNoInheritance(int fd);
		static void setNonBlocking(int fd);

    private:
	
		Fd();
		Fd(const Fd& obj);
		~Fd();
		Fd& operator=(const Fd& obj);
};

#endif