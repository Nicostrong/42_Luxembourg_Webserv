/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 10:24:57 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/Token.hpp"
#include "../../includes/server/Location.hpp"

/*******************************************************************************
 *						CONSTRUCTOR / DESTRUCTOR							   *
 ******************************************************************************/

/*
 *	Default constructor with token
 */
Location::Location( Token*& tokens ): _method(NULL)
{
	try
	{
		createLocation(tokens);
		if (this->_method == NULL)
			this->_method = new MethodHTTP();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return ;
}

/*
 *	Default Location if no location block on the config file
 */
Location::Location( void )
{
	this->_path = "/";
	this->_method = new MethodHTTP();
}

/*
 *	Destructor of Location object, delete all pointer on list of Directive and 
 *	the methodHTTP pointer
 */
Location::~Location( void )
{
	std::list<Directive *>::iterator		itDir;
	std::list<CGIDirective *>::iterator		itCGI;

	delete this->_method;
	for ( itDir = this->_lDirectives.begin(); itDir != this->_lDirectives.end(); ++itDir)
		delete *itDir;
	this->_lDirectives.clear();
	for ( itCGI = this->_lCGIDirectives.begin(); itCGI != this->_lCGIDirectives.end(); ++itCGI)
		delete *itCGI;
	this->_lCGIDirectives.clear();
	return ;
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