/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/29 12:48:49 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Location::Location( std::pair< const std::string, std::string> &data )
	: _name(data.first), _method(NULL)
{
	LOG_DEB("Location constructor called");
	try
	{
		std::string		raw;

		raw = data.second;
		parseData(raw);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	Copy constructor
 */
Location::Location( const Location &src_obj )
	:_name(src_obj._name), _method(src_obj._method), _directives(src_obj._directives)
{
	return ;
}

/*
 *	Destructor
 */
Location::~Location( void )
{
	std::vector<Directive *>::iterator		it;

	LOG_DEB("Location destructor called");
	delete this->_method;
	for ( it = this->_directives.begin(); it != this->_directives.end(); ++it)
		delete *it;
	this->_directives.clear();
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Parsinf of data for Location object
 */
void						Location::parseData( std::string &data )
{
	std::string				directive;
	size_t					pos = data.find_last_of("}");
	
	if (pos != std::string::npos)
		data.erase(pos, 1);
	
	std::istringstream		stream(data);

	while (stream >> directive)
	{
		if (directive == "limit_except")
		{
			std::string data;
			std::string value = directive + " ";

			while (stream >> data && data.find('}') == std::string::npos)
				value += data + " ";
			this->_method = new MethodHTTP(value);
		}
		else
		{
			std::string 	value;
			std::string		temp;
			
			while (stream >> temp && temp.find(';') == std::string::npos)
				value += temp + " ";
			value += temp;
			if (!value.empty() && value[value.size() - 1] == ';')
				value.erase(value.size() - 1);
			if (!directive.empty() && !value.empty())
				this->_directives.push_back(new Directive(directive, value));
		}
	}
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
std::string					Location::getName( void ) const
{
	return (this->_name);
}

/*
 *	get _method value
 */
MethodHTTP					*Location::getMethod( void ) const
{
	return (this->_method);
}

/*
 *	get _directives value
 */
std::vector<Directive *>		Location::getDirectives( void ) const
{
	return (this->_directives);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error creating server
 */
const char		*Location::LocationException::what() const throw()
{
	return  (RED"Error parsing Location !"RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Location const &src_object )
{
	std::vector<Directive>::const_iterator	it;

	out	<< YELLOW << "------------- LOCATION BLOCK -------------" << RESET << std::endl
		<< YELLOW << "Name: " << src_object.getName() << RESET << std::endl;
	if (src_object.getMethod() != NULL)
		out << YELLOW << *src_object.getMethod() << RESET << std::endl;
	/*if (!src_object.getDirectives().empty())
		for (it = src_object.getDirectives().begin(); it != src_object.getDirectives().end(); ++it)
			out << *it;
	*/
	out << YELLOW << "------------------------------------------" << RESET << std::endl;
	return (out);
}

/*******************************************************************************
 *							TESTER CLASS									   *
 ******************************************************************************/

#ifdef LOC
# include <cassert>

int	main( void )
{
	int									i;
	std::map< std::string, std::string>	data;
 
	data["location /"] = "{autoindex off;\nlimit_except GET POST { deny DELETE; }\nroot /var/www/html;}";
	data["location /images"] = "{autoindex on;\nlimit_except GET { deny DELETE POST; }\nroot ./www/images;}";
	data["location /downloads"] = "{autoindex on;\nroot ./www/files;}";
	data["location /redirect"] = "{return\t\t301\thttp://intra.42.fr;}";
	data["location /cgi-bin"] = "{cgi_pass\t\t./lib/cgi-bin;\nfastcgi_pass\t\tunix:/var/run/fcgiwrap.socket;\ninclude\t\tfastcgi_params;}";

	try
	{
		i = 0;
		for (std::map<std::string, std::string>::iterator it = data.begin(); it != data.end(); ++it)
		{
			Location loc(*it);
			std::cout << loc << std::endl;
			std::cout << "✅ [OK] test " << i++ << " passed." << std::endl;
		}
		std::cout << "✅ [OK] ALl test passed." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
 
	return (0);
}
 
#endif