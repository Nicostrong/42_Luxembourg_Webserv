/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fd.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 08:35:46 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/01 08:58:08 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/Fd.hpp"

void Fd::setNoInheritance(int fd)
{
    if (fd <= 2)
        return ;
    
    int flags = fcntl(fd, F_GETFD);

    if (flags == -1 || fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
        throw std::runtime_error("Fcntl failed");
}
