/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserServerConfig.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:39:36 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERSERVERCONFIG_HPP
# define PARSERSERVERCONFIG_HPP

# include "lib.hpp"
# include "Token.hpp"
# include "Ressource.hpp"
# include "CheckerTokens.hpp"

/*
 *	Parser of configfile
 *	- check the extension of config file
 *	- call Ressource to get the content of the file
 *	- check if error with Ressource and get content
 *	- check if the file is empty and start the parsing
 *	- remove all comments
 *	- format the string to remove all spaces and put just one space between each word
 *	- split the file in block of server
 *	- tokenize each block of server
 */
class ParserServerConfig
{

	private:

		std::string					_formatedString;
		Token*						_allTokens;

		ParserServerConfig( void );
		ParserServerConfig( const ParserServerConfig& src );
		ParserServerConfig&			operator=( const ParserServerConfig& src );

		
		void						formatHost( std::string& input );
		void						formatString( const std::string& content );
		void						checkExtension( const std::string& filename );
		void						insertChar( std::string &str, char target, char toInsert );
		
		bool						isValidIPv4( const std::string& ip );
		
		std::string					stripComments( const std::string& line );
		std::string					extractBlock(	const std::string& content,
													const std::string& keyword,
													char end_char, size_t* pos );
		std::string					removeWhitespace( const std::string& input );

	public:

		ParserServerConfig( const std::string& filename );
		~ParserServerConfig( void );

		const Token*&		getAllTokens( void ) const;
		
		/*	EXCEPTION	*/

		/*	Bad extension file	*/
		class	BadExtensionFile : public std::exception
		{
			public:
				const char*		what() const throw();
		};

		/*	Open file config	*/
		class	FileError : public std::exception
		{
			public:
				const char*		what() const throw();
		};


		/*	Empty file config	*/
		class	EmptyConfigError : public std::exception
		{
			public:
				const char*		what() const throw();
		};

		/*	Get server map error	*/
		class	GetServerMapError : public std::exception
		{
			public:
				const char*		what() const throw();
		};
		
};


#endif