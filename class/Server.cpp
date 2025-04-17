/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 15:05:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Server::Server( const std::string &filename )
{
	// try open file throw OpenConfFailException
	// try parsing file throw ParsingErrorException
	(void)filename;
	this->_port = 0;
	this->_maxSizeBody =(5 * 1024 * 1024);	// 5M by default
	this->_name = "webserv";
	this->_adress = "192.168.1.1";
	this->_path = "";
	this->_index = "";
	this->_mError.clear();
	//this->_location.clear();
	initServer(filename);
	LOG_DEB("Server constructor called");
	return ;
}

/*
 *	Destructor
 */
Server::~Server( void )
{
	LOG_DEB("Server destructor called");
	return ;
}


/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

void			Server::setPort( std::string &data )
{
	(void)data;
	this->_port = 0;
	return ;
}

void			Server::setMaxSizeBody( std::string &data )
{
	(void)data;
	this->_maxSizeBody = 0;
	return ;
}

void			Server::setName( std::string &data )
{
	(void)data;
	this->_name = "None";
	return ;
}

void			Server::setAdress( std::string &data )
{
	(void)data;
	this->_adress = "0.0.0.0";
	return ;
}

void			Server::setPath( std::string &data )
{
	(void)data;
	this->_path = "None";
	return ;
}

void			Server::setIndex( std::string &data )
{
	(void)data;
	this->_index = "None";
	return ;
}

void			Server::setMapError( std::string &data )
{
	(void)data;
	this->_mError.insert(std::pair<size_t, std::string>(0, "None"));
	return ;
}

void			Server::setLocation( std::string &data )
{
	(void)data;
	//this->_location.clear();
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _port value
 */
size_t			Server::getPort( void ) const
{
	return (this->_port);
}

/*
 *	get _maxSizeBody value
 */
size_t			Server::getMaxSizeBody( void ) const
{
	return (this->_maxSizeBody);
}

/*
 *	get _name value
 */
std::string		Server::getName( void ) const
{
	return (this->_name);
}

/*
 *	get _adress value
 */
std::string		Server::getAdress( void ) const
{
	return (this->_adress);
}

/*
 *	get _path value
 */
std::string		Server::getPath( void ) const
{
	return (this->_path);
}

/*
 *	get _index value
 */
std::string		Server::getIndex( void ) const
{
	return (this->_index);
}

/*
 *	print all elements of the map
 */
/*
void			Server::getMapError( void ) const
{
	std::map<size_t, std::string>::iterator	it;

	for (it = this->_mError.begin(); it != this->_mError.end(); ++it)
	{
		std::cout	<< "Error number: " << it->first 
					<< " | path page: " << it->second
					<< std::endl;
	}
	return ;
}*/

/*
 *	print all elements of the list Location
 */
/*
void			Server::getLocation( void ) const
{
	std::list<Location>::iterator			it;

	for (it = this->_location.begin(); it != this->_location.end(); ++it)
	{
		std::cout	<< "Error number: " << *it
					<< std::endl;
	}
	return ;
}*/

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/

/*
 *	initialisation of all element of the object Server
 */
void			Server::initServer( const std::string &data )
{
	//	call all setter with the correct value
	(void)data;
	return ;
}
/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

/*
 *	to validate the data
 */
/*
bool			Server::validate( void ) const
{
	return (false);
}*/

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error creating server
 */
const char		*Server::ServerException::what() const throw()
{
	return  (RED"Error creating Server !"RESET);
}

/*
 *	Error openning file.conf
 */
const char		*Server::OpenConfFailException::what() const throw()
{
	return (RED"Error opennig file .conf !"RESET);
}

/*
 *	Error parsing file.conf
 */
const char		*Server::ParsingErrorException::what() const throw()
{
	return (RED"Error parsing file.conf !"RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Server const &src_object )
{
	out	<< GREEN << "SERVER INFORMATION"
		<< "\nname:\t" << src_object.getName()
		<< "\nlisten adress:\t" << src_object.getAdress()
		<< "\nlisten port:\t" << src_object.getPort()
		<< "\nroot path:\t" << src_object.getPath()
		<< "\nindex file:\t" << src_object.getIndex()
		<< "\nmax size of body:\t" << src_object.getMaxSizeBody()
		<< "\nerror pages:\t" << "Afficher la liste des numero erreur | path des pages"
		<< "\nlocation:\t" << "Afficher les blocs des locations"
		<< RESET;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef TEST

int	main( void )
{
	std::string	filename = "monfichier.config";
	Server		obj(filename);
	
	std::cout << obj << std::endl;
	
	return (0);
}

#endif