/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/24 16:16:42 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

/*******************************************************************************
 *								TEMPLATE									   *
 ******************************************************************************/

/*
 *	template to extract a single value from a string
 */
template <typename T>
void			Server::setValue(T &target, std::string &data)
{
	std::string			end;
	std::istringstream	stream(data);

	if (data.empty())
		throw ParsingError(data);
	if (!(stream >> target))
		throw ParsingError(data);
	if (stream >> end)
		throw ParsingError(data);
	return ;
}


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
			setValue(this->_path, const_cast<std::string &>(it->second));
		else if (it->first == "server_name")
			setValue(this->_name, const_cast<std::string &>(it->second));
		else if (it->first == "max_connection_client")
			setValue(this->_maxConnectionClient, const_cast<std::string &>(it->second));
		else if (it->first == "client_max_body_size")
			setMaxSizeBody(const_cast<std::string &>(it->second));
		else if (it->first == "index")
			setValue(this->_index, const_cast<std::string &>(it->second));
		else if (it->first == "error_page")
			setMapError(const_cast<std::string &>(it->second));
		else if (it->first.find("location") == 0)
		{
			std::string	name;

			name = it->first.substr(9);
			setLocation(name, const_cast<std::string &>(it->second));
		}
		else
			throw ParsingError(it->first);
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
		throw PortValueException();
	return ;
}

/*
 *	save the max size of body
 */
void			Server::setMaxSizeBody( std::string &data )
{
	int					value;
	size_t				factor = 1;
	char				unit = 0;
	std::string			numberPart;
	std::istringstream	stream(data);

	if (data.empty())
		throw ParsingError(data);
	if (!(stream >> value))
		throw ParsingError(data);
	if (stream >> unit)
	{
		if (unit == 'M' || unit == 'm')
			factor = 1024 * 1024;
		else if (unit == 'K' || unit == 'k')
			factor = 1024;
		else
			throw ParsingError(data);
	}
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

/*
 *	save the location value
 */
void			Server::setLocation( std::string &name, std::string &block )
{
	std::pair< const std::string, std::string>	locationData(name, block);

	Location									loc(locationData);
	
	this->_location.push_back(loc);
	LOG_DEB("Location added");
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
# include "../includes/HandleConfig.hpp"

int	main( void )
{
	HandleConfig	hg("webserv.conf");

	try
	{
		Server	s(hg.getNicoMap());
		assert(s.getPort() == 8080);
		std::cout << "✅ [OK] get Port test passed." << std::endl;
		assert(s.getAdress() == "127.0.0.1");
		std::cout << "✅ [OK] get Adress test passed." << std::endl;
		assert(s.getName() == "localhost");
		std::cout << "✅ [OK] get Name test passed." << std::endl;
		assert(s.getPath() == "./www/html");
		std::cout << "✅ [OK] get Path test passed." << std::endl;
		assert(s.getMaxSizeBody() == 5242880);
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