/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ip.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:49:43 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:00:35 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IP_HPP
# define IP_HPP

#include "./../lib.hpp"

class Ip
{
	public:
		Ip(const in_addr_t ipv4);
		Ip(const std::string& ipv4);
		Ip(const Ip& obj);
		~Ip();
		Ip&					operator=(const Ip& obj);
		in_addr_t			getIpBytes() const;
		const std::string&	getIpString() const;
		static in_addr_t	ipv4StringToBytes(const std::string& ip);
		static std::string	ipv4BytesToString(in_addr_t ip);
		bool				operator<(const Ip& other) const;
		
	private:
		static bool		isDigits(const std::string& str);
		static size_t	getOctetDecimalValue(const std::string& o);

		in_addr_t 	_ipBytes;
		std::string _ipString;
};

#endif