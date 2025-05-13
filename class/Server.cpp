/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/13 13:43:36 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Server constructor with tokens in argument
 */
Server::Server( Token* serverTokensConfig, EventMonitoring &eventMonitoring) 
	: _maxClient(0), _serverSocket(0), _port(0), _maxSizeBody(0), 
	_path("./www/html"), _index("index.html"), _em(eventMonitoring)
{
	LOG_DEB("Server with tokens Constructor called");
	try
	{
		createServer(serverTokensConfig);
		setAttributs();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	Destructor Server delete all pointer of Location and Directive object
 */
Server::~Server( void )
{
	std::list<Directive *>::iterator				itDir;
	std::map<std::string, Location *>::iterator		itLoc;

	LOG_DEB("Server destructor called");
	cleanup();
	for ( itDir = this->_lDirectives.begin(); itDir != this->_lDirectives.end(); ++itDir)
		delete *itDir;
	this->_lDirectives.clear();
	for ( itLoc = this->_mLocations.begin(); itLoc != this->_mLocations.end(); ++itLoc)
		delete itLoc->second;
	this->_mLocations.clear();
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	read all token and create the object Server with all configuration
 */
void		Server::createServer( Token* tokens )
{
	while (tokens && tokens->getType() != Token::SER_BLK_E)
	{
		if (tokens->getType() == Token::DIR_K)
			createDirective(tokens);
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
 *	create a directive of the server
 */
void		Server::createDirective( Token* tokens )
{
	std::string		key;
	std::string		value;

	while (tokens->getType() != Token::DIR_K)
		tokens = tokens->getNext();
	key = tokens->getValue();
	tokens = tokens->getNext();
	value = tokens->getValue();
	this->_lDirectives.push_back(new Directive(key, value));
	return ;
}

/*
 *	Create a map of code error with the path of the error page
 */
void		Server::createError( Token* tokens )
{
	while (tokens && tokens->getType() != Token::ERR_BLK_E)
	{
		size_t			numError;
		std::string		pathError;

		if (tokens->getType() == Token::SEMICOLON)
			tokens = tokens->getNext();
		while (tokens->getType() != Token::DIR_K)
			tokens = tokens->getNext();
	
		std::stringstream ss(tokens->getValue());
	
		if (!(ss >> numError))
			throw ParsingError(tokens->getValue());
		tokens = tokens->getNext();
		pathError = tokens->getValue();
		this->_mError.insert( std::pair<size_t, std::string>(numError, pathError));
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
		std::string		key = (*it)->getKey();
		std::string		value = (*it)->getValue();

		if (key == "listen")
			setPort(value);
		else if (key == "root")
			this->_path = value;
		else if (key == "server_name")
			this->_name = value;
		else if (key == "max_connection_client")
			setMaxClient(value);
		else if (key == "client_max_body_size")
			setMaxSizeBody(value);
		else if (key == "index")
			this->_index = value;
		else
			throw ParsingError(key);
	}
	return ;
}

/*
 *	When a client close the connection, it close the socket and remove its from the list
 */
void Server::cleanup()
{
	std::list<Socket>::const_iterator it = this->_lSockets.begin();;
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
}

/*******************************************************************************
 *								SETTER										   *
 ******************************************************************************/

/*
 *	Transform the string in size_t type for the port and check the value
 */
void			Server::setPort( std::string data )
{
	size_t					port;
	std::stringstream		ss(data);
	
	if (!(ss >> port))
			throw ParsingError(data);
	if (port <= 0 || port > 65535)
		throw PortValueException();
	this->_port = port;
	return ;
}

/*
 *	Transform the string in size_t and apply a factor for the final value
 */
void			Server::setMaxSizeBody( std::string data )
{
	size_t					value;
	size_t					factor = 1;
	char					unit = 0;
	std::string				numberPart;
	std::istringstream		stream(data);

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
	}
	this->_maxSizeBody = value * factor;
	return ;
}

/*
 *	Transform the string in int type for the number of client can connect
 */
void			Server::setMaxClient( std::string data )
{
	int						clients;
	std::stringstream		ss(data);
	
	if (!(ss >> clients))
			throw ParsingError(data);
	if (clients <= 0)
		clients = 10;
	this->_maxClient = clients;
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _maxConnectionClient value
 */
const int&			Server::getMaxClient( void ) const { return (this->_maxClient); }

/*
 *	get _port value
 */
const size_t&		Server::getPort( void ) const { return (this->_port); }

/*
 *	get _maxSizeBody value
 */
const size_t&		Server::getMaxSizeBody( void ) const{ return (this->_maxSizeBody); }

/*
 *	get _name value
 */
const std::string&	Server::getName( void ) const { return (this->_name); }

/*
 *	get _path value
 */
const std::string&	Server::getPath( void ) const { return (this->_path); }

/*
 *	get _index value
 */
const std::string&	Server::getIndex( void ) const { return (this->_index); }

/*
 *	get _mError value
 */
const std::map<size_t, std::string>&	Server::getMapError( void ) const { return (this->_mError); }


/*
 *	get all Location object of the server
 */
const std::map<std::string, Location *>	Server::getAllLocation( void ) const { return (this->_mLocations); }

/*
 *	get all value of Location
 */

const Location&			Server::getLocations( std::string path ) const
{
	std::map<std::string, Location*>::const_iterator		it;
	
	it = _mLocations.find(path);
	if (it != _mLocations.end())
		return (*(it->second));
	throw std::runtime_error("Location not found");
}

/*
 *	return the path of the code error in argument
 */
const std::string		Server::getPathError( size_t error_code ) const
{
	std::map<size_t, std::string>::const_iterator		it;
	
	it = _mError.find(error_code);
	if (it != _mError.end())
		return (it->second);
	throw std::runtime_error("Error code not fund");
}

/*******************************************************************************
 *							SERVER EVENTS									   *
 ******************************************************************************/

void Server::start()
{
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->getPort());
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

void Server::onReadEvent(int fd, int type, EventMonitoring& em)
{
	(void)fd;
	int clientSocket = accept(this->_serverSocket, NULL, NULL);
	if (clientSocket == -1)
	{
		return;
		//Failed accepting the client socket
	}
	Socket s(clientSocket, em, *this);
	this->_lSockets.push_front(s);
	em.monitor(clientSocket, POLLIN | POLLOUT| POLLHUP | POLLRDHUP,
		 EventData::CLIENT, *_lSockets.begin());
	if (type == EventData::SERVER)
		std::cout << "Incoming socket request" << std::endl;
}

void Server::onWriteEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}

void Server::onCloseEvent(int fd, int type, EventMonitoring& em)
{
	(void)em;
	(void)fd;
	(void)type;
}

void Server::onSocketClosedEvent(const Socket& s)
{
	this->_em.unmonitor(s.getSocket());
	close(s.getSocket());
	this->_lSockets.remove(s);
	std::cout << "A client has disconnected" << std::endl;
}

/*******************************************************************************
 *								CHECKER										   *
 ******************************************************************************/

/*
 *	Check if the uri is in Location object or not
 */
bool							Server::checkUri( std::string uri )
{
	std::map<std::string, Location *>::iterator		it;

	it = _mLocations.find(uri);
	if (it != _mLocations.end())
		return (true);
	return (false);
}

const Location*						Server::getUri( const std::string& uri )
{
	std::map<std::string, Location *>::iterator		it;
	Location* 										bestMatch = NULL;
	
	for (it = this->_mLocations.begin(); it != this->_mLocations.end(); it++)
	{
		if(it->second->isMatching(uri))
		{
			if (!bestMatch || 
					bestMatch->getPath().size() < it->second->getPath().size())
				bestMatch = it->second;
		}
	}
	if (bestMatch)
		LOG_DEB("Best match found for " + uri + " is " + bestMatch->getPath());
	else
		LOG_DEB("No match found for " + uri);
	return (bestMatch);
}

/*
 *	Check if a method is allowed in a Location scope
 */
bool	Server::checkMethod( std::string uri, std::string method )
{
	std::map<std::string, Location *>::iterator		it;
	Location*										locDef = NULL;
	Location*										locExist = NULL;

	for (it = this->_mLocations.begin(); it != this->_mLocations.end(); ++it)
	{
		if (it->second->getPath() == "/")
			locDef = it->second;
		if (it->second->getPath() == uri)
			locExist = it->second;
	}
	return (locExist ? locExist->getMethod()->isAllowed(method) :
           locDef ? locDef->getMethod()->isAllowed(method) : false);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Creation class Exception for parsing error with data
 */
Server::ParsingError::ParsingError( const std::string &data ) throw()
{
	this->_msg = RED"[ERROR] Parsing data: " + data + RESET;
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
	return  (RED "[ERROR] Creating Server !" RESET);
}

/*
 *	Port value exception
 */
const char		*Server::PortValueException::what() const throw()
{
	return (RED "[ERROR] Value of port not correct !" RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Server const &src_object )
{
	std::map<size_t, std::string>::const_iterator		it;
	std::map<size_t, std::string>						mError;
	const std::map<std::string, Location *>				loc = src_object.getAllLocation();
	
	mError = src_object.getMapError();
	
	out	<< GREEN << "================= SERVER CONFIG =================" << RESET << std::endl
		<< GREEN << "Name:\t\t\t" << src_object.getName() << RESET <<std::endl
		<< GREEN << "Listen adress:\t\t127.0.0.1" << RESET << std::endl
		<< GREEN << "Listen port:\t\t" << src_object.getPort() << RESET << std::endl
		<< GREEN << "Root path:\t\t" << src_object.getPath() << RESET << std::endl
		<< GREEN << "Index file:\t\t" << src_object.getIndex() << RESET << std::endl
		<< GREEN << "Max connection client:\t" << src_object.getMaxClient() << RESET << std::endl
		<< GREEN << "Max size of body:\t" << src_object.getMaxSizeBody() << " bytes." << RESET << std::endl
		<< GREEN << "Error pages:" << RESET << std::endl;
	
	for (it = mError.begin(); it != mError.end(); ++it)
		out << GREEN << "\t" << it->first << " => " << it->second << RESET << std::endl;
	
	out << GREEN << "Locations:" << RESET << std::endl;	
	for (std::map<std::string, Location *>::const_iterator it = loc.begin(); it != loc.end(); ++it)
		out << it->second << RESET << std::endl;
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