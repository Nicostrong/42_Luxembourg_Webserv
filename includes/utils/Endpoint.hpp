/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Endpoint.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:53:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:40:40 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDPOINT_HPP
# define ENDPOINT_HPP

# include "./Ip.hpp"
# include "../lib.hpp"

class   Endpoint
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

std::ostream& operator<<(std::ostream& os, const Endpoint& obj);

#endif