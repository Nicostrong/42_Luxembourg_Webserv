/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_p.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:41:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 10:23:10 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	read all token and create the object Server with all configuration
 */
void		Server::createServer( Token*& tokens )
{
	while (tokens && tokens->getType() != Token::SER_BLK_E)
	{
		if (tokens->getType() == Token::DIR_K)
			this->_lDirectives.push_back(new Directive(tokens));
		else if (tokens->getType() == Token::ERROR_PAGE)
			createError(tokens);
		else if (tokens->getType() == Token::LOCATION)
		{
			Location*		loc = new Location(tokens);
			
			this->_mLocations.insert(std::make_pair(loc->getPath(), loc));
		}
		tokens = tokens->getNext();
	}
	return ;
}

/*
 *	Create a map of code error with the path of the error page
 */
void		Server::createError( Token*& tokens )
{
	tokens = tokens->getNext()->getNext();
	while (tokens && tokens->getType() != Token::ERR_BLK_E)
	{
		size_t				numError;
		std::string			pathError;
		std::stringstream	ss(tokens->getValue());
		
		if (!(ss >> numError))
			throw ParsingError("conversion error " + tokens->getValue());
		tokens = tokens->getNext();
		pathError = tokens->getValue();
		this->_mError.insert( std::pair<size_t, std::string>(numError, pathError));
		tokens = tokens->getNext()->getNext();
	}
	return ;
}

/*
 *	Read all directive and set somes attributes
 */
void		Server::setAttributs( void )
{
	std::list<Directive *>::iterator		it;

	for (it = this->_lDirectives.begin(); it != this->_lDirectives.end(); ++it)
	{
		std::string						key = (*it)->getKey();
		std::list<std::string>		values = (*it)->getValues();

		if (key == "listen")
			setPort(values);
		if (key == "host")
			this->_serverIp = *values.begin();
		else if (key == "root")
			this->_path = *values.begin();
		else if (key == "server_name")
			this->_lHost.insert(_lHost.end(), values.begin(), values.end());
		else if (key == "max_connection_client")
			setMaxClient(*values.begin());
		else if (key == "client_max_body_size")
			setMaxSizeBody(*values.begin());
		else if (key == "index")
			this->_index = *values.begin();
	}
	return ;
}

/*
 *	When a client close the connection, it close the socket and remove its from the list
 */
void		Server::cleanup( void )
{
	std::list<Socket>::const_iterator		it = this->_lSockets.begin();

	while (it != this->_lSockets.end())
	{
		this->_em.unmonitor(it->getSocket());
		if (this->_serverSocket > 2)
			close(it->getSocket());
		++it;
	}
	this->_lSockets.clear();
	this->_em.unmonitor(this->_serverSocket);
	if (this->_serverSocket > 2)
		close(this->_serverSocket);
	std::cout << "Server closed" << std::endl;
	return ;
}
