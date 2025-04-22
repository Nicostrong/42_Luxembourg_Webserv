/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 18:19:07 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Location::Location( std::map<std::string, std::string> &data ) : _method()
{
	std::string			raw;
	std::string			line;

	if (data.size() != 1)
		throw LocationException();
	this->_name = data.begin()->first;
	raw = data.begin()->second;
	raw.erase(0, raw.find("{") + 1);
	raw.erase(raw.find_last_of("}"));

	std::istringstream	stream(raw);

	while (std::getline(stream, line))
	{
		std::string			directive;
		std::istringstream	lineStream(line);

		lineStream >> directive;
		if (directive == "limit_except")
		{
			std::string limitData;
			
			limitData = line;
			while (line.find("}") == std::string::npos && std::getline(stream, line))
				limitData += "\n" + line;
			this->_method = MethodHTTP(limitData);
		}
		else
		{
			std::string value;

			lineStream >> value;
			if (!value.empty() && value[value.size() - 1] == ';')
				value.erase(value.size() - 1);
			this->_directives[directive] = Directive(value);
		}
	}
	LOG_DEB("Location constructor called");
	return ;
}

/*
 *	Destructor
 */
Location::~Location( void )
{
	LOG_DEB("Location destructor called");
	return ;
}

/*******************************************************************************
 *								GETTER										   *
 ******************************************************************************/

/*
 *	get _name value
 */
std::string							Location::getName( void ) const
{
	return (this->_name);
}

/*
 *	get _method value
 */
MethodHTTP							Location::getMethod( void ) const
{
	return (this->_method);
}

/*
 *	get _directives value
 */
std::map<std::string, Directive>	Location::getDirectives( void ) const
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
	std::map<std::string, Directive>::const_iterator	it;

	out	<< GREEN << "LOCATION INFORMATION" << std::endl
		<< src_object.getMethod() << std::endl;
	for (it = src_object.getDirectives().begin(); it != src_object.getDirectives().end(); ++it)
		out << "- " << it->first << " => [" << it->second.getAllValue() << "]" << std::endl;
	out << RESET;
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
 
	data["location /"] = "{autoindex off;\nlimit_except GET POST { deny DELETE; }\nroot /var/www/html;}";
	data["location /images"] = "{autoindex on;\nlimit_except GET { deny DELETE POST; }\nroot ./www/images;}";
	data["location /downloads"] = "{autoindex on;\nroot ./www/files;}";
	data["location /redirect"] = "{return\t\t301\thttp://intra.42.fr;}";
	data["location /cgi-bin"] = "{cgi_pass\t\t./lib/cgi-bin;\nfastcgi_pass\t\tunix:/var/run/fcgiwrap.socket;\ninclude\t\tfastcgi_params;}";

	try
	{
		Location	loc(data);
		std::cout << "✅ [OK] get Index test passed." << std::endl;
		std::cout << loc << std::endl;
		std::cout << "✅ [OK] Serverbasic config test passed." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
 
	return (0);
}
 
 #endif