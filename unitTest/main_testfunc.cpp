/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_testfunc.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:40:32 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 21:00:55 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/Ip.hpp"
#include "./../includes/lib.hpp"

int main(void)
{
    std::cout << Ip::ipv4BytesToString(Ip::ipv4StringToBytes("0.0.0.1")) << std::endl;
    return (0);
}