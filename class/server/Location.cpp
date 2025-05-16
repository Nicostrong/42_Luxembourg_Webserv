/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 11:37:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Location.hpp"
#include "../../includes/Token.hpp"

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
 *	Destructor of Location object, delete all pointer on list of Directive and 
 *	the methodHTTP pointer
 */
Location::~Location( void )
{
	std::list<Directive *>::iterator		it;

	delete this->_method;
	for ( it = this->_lDirectives.begin(); it != this->_lDirectives.end(); ++it)
		delete *it;
	this->_lDirectives.clear();
	return ;
}

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Read all Location tokens and create the Location object
 */
void						Location::createLocation( Token*& tokens )
{
	this->_path = tokens->getValue();
	while (tokens && tokens->getType() != Token::LOC_BLK_E)
	{
		if (tokens->getType() == Token::DIR_K)
			this->_lDirectives.push_back(new Directive(tokens));
		else if (tokens->getType() == Token::HTTP_K && !this->_method)
			this->_method = new MethodHTTP(tokens);
		else if (tokens->getType() == Token::CGI_K)
			this->_lCGIDirectives.push_back(new CGIDirective(tokens));
		tokens = tokens->getNext();
	}
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
	return  (RED "Error parsing Location !" RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Location const &src_object )
{
	std::list<Directive *>::const_iterator	it;

	out	<< YELLOW << "------------- LOCATION BLOCK -------------" << RESET << std::endl
		<< YELLOW << "Name: " << src_object.getPath() << RESET << std::endl;
	if (src_object.getMethod() != NULL)
		out << YELLOW << *src_object.getMethod() << RESET << std::endl;
	if (!src_object.getDirectives().empty())
		for (it = src_object.getDirectives().begin(); it != src_object.getDirectives().end(); ++it)
		{
			if (*it)
				out << **it;
			else
				out << "[ERROR] Directive invalide détectée !" << std::endl;
		}
	
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