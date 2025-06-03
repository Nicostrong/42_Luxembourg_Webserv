/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ip.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:49:43 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/03 17:11:57 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IP_HPP
# define IP_HPP

#include "lib.hpp"

class Ip
{
    public:
		Ip(const in_addr_t ipv4);
		Ip(const std::string& ipv4);
		Ip(const Ip& obj);
		~Ip();
		Ip& operator=(const Ip& obj);
		static in_addr_t ipv4StringToBytes(const std::string& ip);
    private:		
		in_addr_t 	_ipBytes;
		std::string _ipString;
};

#endif