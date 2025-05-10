/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/10 17:02:12 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef N
# define N

# include "./lib.hpp"
# include "./Ressource.hpp"

class Token;
/*
 *	Parser of configfile
 *	- check the file (hidden file, extension)
 *	- call Ressource to get the content of the file
 *	- check if error with Ressource and get content
 *	- check if the file is empty and strat parsing
 *	- split the file in block of server
 *	- remove all comments
 *	- tokenize each block of server
 */
class ParserServerConfig
{

	private:

		std::string				_formatedString;
		Token*					_allTokens;
		std::list<Token*>		_serverToken;

		ParserServerConfig( void );
		ParserServerConfig( const ParserServerConfig& src );
		ParserServerConfig&		operator=( const ParserServerConfig& src );

		int						parsePort( const std::string& value );

		void					checkHiddenFile( const std::string& filename );
		void					formatString( const std::string& content );
		void					insertChar( std::string &str, char target, char toInsert );
		void					debugTokens( const std::vector<Token>& tokens, int indent);

		std::string				extractBlock(	const std::string& content,
												const std::string& keyword,
												char end_char, size_t* pos);
		std::string				stripComments( const std::string& line );
		std::string				removeWhitespace( const std::string& input );

	public:

		ParserServerConfig( const std::string& filename );
		~ParserServerConfig( void );

		/*	parsing error Exception	*/
		class	ParsingError: public std::exception
		{
			private:
				std::string				_msg;
			public:
				ParsingError( const std::string& data ) throw();
				virtual ~ParsingError( void ) throw();
				virtual const char	*what() const throw();
		
		};

		/*	Open file config	*/
		class	FileError : public std::exception
		{
			public:
				const char	*what() const throw();
		};
		
		/*	Hidden file config	*/
		class	HiddenFile : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		/*	Bad extension file	*/
		class	BadExtensionFile : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		/*	Empty file config	*/
		class	EmptyConfigError : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		/*	Brace error	*/
		class	BraceError : public std::exception
		{
			public:
				const char	*what() const throw();
		};

		/*	Get server map error	*/
		class	GetServerMapError : public std::exception
		{
			public:
				const char	*what() const throw();
		};
		
		/*	port value error Exception	*/
		class	PortValueException : public std::exception
		{
			public:
				const char	*what() const throw();
		};
		
};


#endif