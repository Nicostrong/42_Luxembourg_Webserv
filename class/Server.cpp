/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 17:21:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Server::Server( std::map< std::string, std::string> const &data )
{
	std::map< std::string, std::string>::const_iterator	it;

	for (it = data.begin(); it != data.end(); ++it)
	{
		if (it->first == "listen")
		{
			setAdress(const_cast<std::string &>(it->second));
			setPort(const_cast<std::string &>(it->second));
		}
		else if (it->first == "root")
			setPath(const_cast<std::string &>(it->second));
		else if (it->first == "server_name")
			setName(const_cast<std::string &>(it->second));
		else if (it->first == "client_max_body_size")
			setMaxSizeBody(const_cast<std::string &>(it->second));
		else if (it->first == "index")
			setIndex(const_cast<std::string &>(it->second));
		else if (it->first == "error_page")
			setMapError(const_cast<std::string &>(it->second));
#ifndef TEST
		else if (it->first.find("location") == 0)
			setLocation(const_cast<std::string &>(it->second));
		else
			throw ParsingError(it->first);
#endif
	}
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

/*
 *	extract the adress from the string
 */
void			Server::setAdress( std::string &data )
{
	size_t	pos = data.find(":");

	if (pos == std::string::npos)
		throw ParsingError(data);
	this->_adress = data.substr(0, pos);
	return ;
}

/*
 *	extract the port from the string
 */
void			Server::setPort( std::string &data )
{
	size_t	pos = data.find(":");
	
	if (pos == std::string::npos)
		throw ParsingError(data);
	this->_port = static_cast<size_t>(std::atoi(data.substr(pos + 1).c_str()));
	if (this->_port < 0 || this->_port > 65535)
		throw ParsingError(data);
	return ;
}

/*
 *	save the name of the server
 */
void			Server::setName( std::string &data )
{
	if (data.empty())
		throw ParsingError(data);
	this->_name = data;
	return ;
}

/*
 *	set the path value
 */
void			Server::setPath( std::string &data )
{
	if (data.empty())
		throw ParsingError(data);
	this->_path = data;
	return ;
}

/*
 *	set the index value
 */
void			Server::setIndex( std::string &data )
{
	if (data.empty())
		throw ParsingError(data);
	this->_index = data;
	return ;
}

/*
 *	save the max size of body
 */
void			Server::setMaxSizeBody( std::string &data )
{
	int			value;
	size_t		factor;
	char		unit;
	std::string	numberPart;

	if (data.empty())
		throw ParsingError(data);
	factor = 1;
	unit = data[data.size() - 1];
	if (isdigit(unit))
		numberPart = data;
	else
	{
		numberPart = data.substr(0, data.size() - 1);
		if (unit == 'M' || unit == 'm')
			factor = 1024 * 1024;
		else if (unit == 'K' || unit == 'k')
			factor = 1024;
		else
			throw ParsingError(data);
	}
	for (size_t i = 0; i < numberPart.size(); ++i)
		if (!isdigit(numberPart[i]))
			throw ParsingError(numberPart);
	value = std::atoi(numberPart.c_str());
	this->_maxSizeBody = static_cast<size_t>(value) * factor;
	return ;
}

/*
 *	save the map of error page
 */
void			Server::setMapError( std::string &data )
{
	std::istringstream	stream(data);
	std::string			line;

	while (std::getline(stream, line))
	{
		std::istringstream	lineStream(line);
		int					code;
		std::string			path;

		lineStream >> code >> path;
		if (!path.empty())
			path.erase(path.find_last_of(';'));
		this->_mError[code] = path;
	}
	return ;
}

#ifndef TEST
/*
 *	save the location value
 */
void			Server::setLocation( std::string &data )
{
	if (data.empty())
		throw ParsingError(data);
	
	Location		loc(data);
	this->_location.push_back(loc);
	LOG_DEB("Location added");
	return ;
}
#endif

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
 *	get _mError value
 */
std::map<size_t, std::string>	Server::getMapError( void ) const
{
	return (this->_mError);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsing error with data
 */
Server::ParsingError::ParsingError( const std::string &data ) throw()
{
	this->_msg = RED"Error parsing data: " + data + RESET;
	return ;
}
/*
 *	Destructor for ParsingError
 */
Server::ParsingError::~ParsingError( void ) throw()
{
	return ;
}
/*
 *	Error parsing file.conf
 */
const char		*Server::ParsingError::what() const throw()
{
	return (this->_msg.c_str());
}

/*
 *	Error creating server
 */
const char		*Server::ServerException::what() const throw()
{
	return  (RED"Error creating Server !"RESET);
}


/*
 *	Port value exception
 */
const char		*Server::PortValueException::what() const throw()
{
	return (RED"Value of port not correct !"RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Server const &src_object )
{
	std::map<size_t, std::string>::const_iterator	it;
	std::map<size_t, std::string>					mError;
	mError = src_object.getMapError();

	out	<< GREEN << "SERVER INFORMATION" << std::endl
		<< "name:\t" << src_object.getName() << std::endl
		<< "listen adress:\t" << src_object.getAdress() << std::endl
		<< "listen port:\t" << src_object.getPort() << std::endl
		<< "root path:\t" << src_object.getPath() << std::endl
		<< "index file:\t" << src_object.getIndex() << std::endl
		<< "max size of body:\t" << src_object.getMaxSizeBody() << std::endl
		<< "error pages:" << std::endl;
	for (it = mError.begin(); it != mError.end(); ++it)
		out << "\t" << it->first << " => " << it->second << std::endl;
	out << "location:\t" << "Afficher les blocs des locations"
		<< RESET;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef TEST
# include <cassert>

int	main( void )
{
	std::map< std::string, std::string>	data;
	
	data["listen"] = "127.0.0.1:8080";
	data["server_name"] = "localhost";
	data["root"] = "./www/html";
	data["client_max_body_size"] = "10M";
	data["index"] = "index.html";
	data["error_page"] = "404 ./errors/404.html;\n500 ./errors/500.html;";
	data["location /"] = "autoindex on;\nlimit_except GET POST { deny DELETE; }\nroot /var/www/html;";

	try
	{
		Server	s(data);
		assert(s.getPort() == 8080);
		std::cout << "✅ [OK] get Port test passed." << std::endl;
		assert(s.getAdress() == "127.0.0.1");
		std::cout << "✅ [OK] get Adress test passed." << std::endl;
		assert(s.getName() == "localhost");
		std::cout << "✅ [OK] get Name test passed." << std::endl;
		assert(s.getPath() == "./www/html");
		std::cout << "✅ [OK] get Path test passed." << std::endl;
		assert(s.getMaxSizeBody() == 10485760);
		std::cout << "✅ [OK] get MaxSizeBody test passed." << std::endl;
		assert(s.getIndex() == "index.html");
		std::cout << "✅ [OK] get Index test passed." << std::endl;
		std::cout << s << std::endl;
		std::cout << "✅ [OK] Serverbasic config test passed." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}

#endif