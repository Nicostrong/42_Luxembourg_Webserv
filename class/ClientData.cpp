/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:34:04 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 18:58:21 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ClientData.hpp"
#include "../includes/BaseData.hpp"

ClientData::ClientData() : BaseData(CLIENT), _reiceived(""),
						   _reiceivedCount(0) {}

ClientData::ClientData(const ClientData &obj) : BaseData(obj), _reiceived(""),
												_reiceivedCount(0)
{
	*this = obj;
}

ClientData::~ClientData() {}

ClientData &ClientData::operator=(const ClientData &obj)
{
	if (this != &obj)
	{
		this->_reiceived = obj._reiceived;
		this->_reiceivedCount = obj._reiceivedCount;
	}
	return (*this);
}

void ClientData::readReceived(int clientSocket, int serverSocket)
{
	std::vector<char> buffer(BUFFER_SIZE);
	ssize_t bytes;

	if (clientSocket > -1 && serverSocket > -1)
	{
		while ((bytes = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0)) == 
				BUFFER_SIZE)
			this->_reiceived.append(buffer.data(), bytes);
		if (bytes == -1)
		{
			this->_reiceived.clear();
			throw SocketReadException();
		}
		this->_reiceived.append(buffer.data(), bytes);
		std::cout << this->_reiceived << "size = " << this->_reiceived.size() << " Last content = " << (int)buffer[bytes - 2] << " " << (int)buffer[bytes - 1] << std::endl;
		this->_reiceivedCount++;
		return;
	}
}