/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fd.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 08:36:55 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/01 14:48:49 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_HPP
# define FD_HPP

#include "./../lib.hpp"

class Fd
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