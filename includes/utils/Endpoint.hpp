/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Endpoint.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:53:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:29:19 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDPOINT_HPP
# define ENDPOINT_HPP

#include "./../lib.hpp"
#include "./Ip.hpp"

class Endpoint
{
    public:
        Endpoint(const Ip& ip, size_t port);
        Endpoint(const Endpoint& obj);
        ~Endpoint();
        Endpoint& operator=(const Endpoint& obj);

		const Ip&		getIp() const;
		size_t			getPort() const;

		static Endpoint	getEntryAddress(int fd);
		static Endpoint	getEndpoint(sockaddr_in endpoint);
    private:
        Ip		_ip;
        size_t	_port;
        
};

#endif