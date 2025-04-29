/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/28 13:29:48 by nfordoxc         ###   Luxembourg.lu     */
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
		throw ParsingError("Data empty or not catched");
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
 *	Parsing of the map<string, string> who contain all value of the config file
 *	to create an object Server
 */
Server::Server( std::map< std::string, std::string> const &data, 
	EventMonitoring &eventMonitoring) : _port(0), _maxConnectionClient(0), 
	_maxSizeBody(0), _em(eventMonitoring), _serverSocket(0)
{
	try
	{
		parseData(data);
		checkServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	LOG_DEB("Server constructor called");
	return ;
}

// Simple Constructor

Server::Server(EventMonitoring &eventMonitoring) : 
	_em(eventMonitoring), _serverSocket(0)
{
	LOG_DEB("Simple Server Constructor called");
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
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Parsing of the map data
 */
void		Server::parseData( const std::map< std::string, std::string> &data )
{
	std::map< std::string, std::string>::const_iterator		it;

	for (it = data.begin(); it != data.end(); ++it)
	{
		std::string		value = it->second;

		if (it->first == "listen")
		{
			setAdress(value);
			setPort(value);
		}
		else if (it->first == "root")
			setValue(this->_path, value);
		else if (it->first == "server_name")
			setValue(this->_name, value);
		else if (it->first == "max_connection_client")
			setValue(this->_maxConnectionClient, value);
		else if (it->first == "client_max_body_size")
			setMaxSizeBody(value);
		else if (it->first == "index")
			setValue(this->_index, value);
		else if (it->first == "error_page")
			setMapError(value);
		else if (it->first.find("location") == 0)
		{
			std::string	name;

			name = it->first.substr(8);
			setLocation(name, value);
		}
		else
			throw ParsingError(it->first);
	}
	return ;
}

/*
 *	Check if the Server contain correct value
 */
void		Server::checkServer( void )
{
	if (this->_port == 0)
		throw ParsingError("port = 0");
	if (this->_maxConnectionClient == 0)
		throw ParsingError("max connection client = 0");
	if (this->_maxSizeBody == 0)
		throw ParsingError("max size body = 0");
	if (this->_name.empty())
		throw ParsingError("name is empty");
	if (this->_adress.empty())
		throw ParsingError("adress is empty");
	if (this->_path.empty())
		throw ParsingError("path is empty");
	if (this->_index.empty())
		throw ParsingError("index is empty");
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
	if (this->_port <= 0 || this->_port > 65535)
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
	int					code;
	std::string			path;

	while (stream >> code >> path)
	{
		if (!path.empty() && path[path.size() - 1] == ';')
			path.erase(path.size() - 1);
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

/*
 *	get all value of Location
 */

std::list<Location>				Server::getLocations( void ) const
{
	return (this->_location);
}

// Server events and exec

void Server::start()
{
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Socket failed to be created" << std::endl;
		return ;
	}

	int opt = 1;

	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		std::cerr << "Setsockopt failed: " << strerror(errno) << std::endl;
		return ;
	}

	if (bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		std::cerr << "Socket failed to start listening" << std::endl;
		return ;
	}
	if (listen(serverSocket, 5) == -1)
	{
		std::cerr << "Socket faield to start listening" << strerror(errno) << std::endl;
		return ;
	}
	std::cout << "Listening on port 8080" << std::endl;
	
	this->_serverSocket = serverSocket;
	this->_em.monitor(serverSocket, POLLIN, EventData::SERVER, 
		*this);
	while (1)
		this->_em.updateEvents();
}

void Server::onReadEvent(int fd, int type)
{
	(void)fd;
	int clientSocket = accept(this->_serverSocket, NULL, NULL);
	if (clientSocket == -1)
	{
		return;
		//Failed accepting the client socket
	}
	Socket s(clientSocket, this->_em, *this);
	this->_sockets.push_front(s);
	this->_em.monitor(clientSocket, POLLIN | POLLOUT| POLLHUP | POLLRDHUP,
		 EventData::CLIENT, *_sockets.begin());
	if (type == EventData::SERVER)
		std::cout << "Incoming socket request" << std::endl;
}

void Server::onWriteEvent(int fd, int type)
{
	(void)fd;
	(void)type;
}

void Server::onCloseEvent(int fd, int type)
{
	(void)fd;
	(void)type;
}

void Server::onSocketClosedEvent(const Socket& s)
{
	this->_em.unmonitor(s.getSocket());
	close(s.getSocket());
	this->_sockets.remove(s);
	std::cout << "A client has disconnected" << std::endl;
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
	return  (RED "Error creating Server !" RESET);
}

/*
 *	Port value exception
 */
const char		*Server::PortValueException::what() const throw()
{
	return (RED "Value of port not correct !" RESET);
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
	const std::list<Location>						&loc = src_object.getLocations();
	
	mError = src_object.getMapError();
	
	out	<< GREEN << "================= SERVER CONFIG =================" << RESET << std::endl
		<< GREEN << "Name:\t\t\t" << src_object.getName() << RESET <<std::endl
		<< GREEN << "Listen adress:\t\t" << src_object.getAdress() << RESET << std::endl
		<< GREEN << "Listen port:\t\t" << src_object.getPort() << RESET << std::endl
		<< GREEN << "Root path:\t\t" << src_object.getPath() << RESET << std::endl
		<< GREEN << "Index file:\t\t" << src_object.getIndex() << RESET << std::endl
		<< GREEN << "Max size of body:\t" << src_object.getMaxSizeBody() << " bytes." << RESET << std::endl
		<< GREEN << "Error pages:" << RESET << std::endl;
	
	for (it = mError.begin(); it != mError.end(); ++it)
		out << GREEN << "\t" << it->first << " => " << it->second << RESET << std::endl;
	
	out << GREEN << "Locations:" << RESET << std::endl;	
	for (std::list<Location>::const_iterator it = loc.begin(); it != loc.end(); ++it)
		out << *it << RESET << std::endl;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef SER

# include <cassert>
# include "../includes/HandleConfig.hpp"

int	main( void )
{
	HandleConfig	hg("webserv.conf");

	try
	{
		Server	s(hg.getwebconfMap());
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