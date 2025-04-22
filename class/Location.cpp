/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/22 15:57:31 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Location::Location( std::string &data ) : _method()
{
	std::string	clean;
	std::string	line;

	clean = data;
	clean.erase(0, clean.find("{") + 1);
	clean.erase(clean.find_last_of("}"));
	std::istringstream	stream(clean);
	while (std::getline(stream, line))
	{
		std::string			directive;
		std::istringstream	lineStream(line);

		lineStream >> directive;
		if (directive == "limit_except")
		{
			std::string limitData;
			
			limitData = line.substr(line.find("limit_except"));
			this->_method = MethodHTTP(limitData);
		}
		else
		{
			std::string value;
			lineStream >> value;
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
	out	<< GREEN << "LOCATION INFORMATION"
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
 
	data["location /"] = "autoindex off;\nlimit_except GET POST { deny DELETE; }\nroot /var/www/html;";
	data["location /images"] = "autoindex on;\nlimit_except GET { deny DELETE POST; }\nroot ./www/images;";
	data["location /downloads"] = "autoindex on;\nroot ./www/files;";
	data["location /redirect"] = "return\t\t301\thttp://intra.42.fr;";
	data["location /cgi-bin"] = "cgi_pass\t\t./lib/cgi-bin;\nfastcgi_pass\t\tunix:/var/run/fcgiwrap.socket;\ninclude\t\tfastcgi_params;";

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