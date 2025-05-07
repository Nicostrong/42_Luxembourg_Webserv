/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/07 11:14:32 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef N
# define N

# include "./lib.hpp"
# include "./EventMonitoring.hpp"
# include "./Ressource.hpp"

/*
 *	The parser take the filename in argument.
 *	Check if it's a valid file (extension) and call Ressource.
 *	It call a function who read the file and return the part for one server.
 *	With this part, it creat a map with all element of the server.
 *	Key are the first and the second word (for location) and the value the part
 *	between '{}' or the value before the ';'.
 *	when all the file is read, it contain a map of server config.
 *	The Key is the value of the listening port and the value a map of config for
 *	one server.
 */
class ParserServerConfig
{

	private:

		std::map<int, std::map<std::string, std::string> >		_servers;

		ParserServerConfig( void );
		ParserServerConfig( const ParserServerConfig& src );
		ParserServerConfig&		operator=( const ParserServerConfig& src );

		int						parsePort( const std::string& value );

		bool					requireSemicolon( const std::string& line );

		void					checkHiddenFile( const std::string& filename );
		void					parseConfigFile( const std::string& content );
		void					parseServerBlock( const std::string& serverBlock );

		std::string				trim( const std::string& s );
		std::string				extractBlock(	const std::string& content,
												const std::string& keyword,
												char end_char, size_t* pos);
		std::string				stripComments( const std::string& line );

	public:

		ParserServerConfig( std::string filename );
		~ParserServerConfig( void );

		/*	GETTER	*/
		const std::map<std::string, std::string>&	getServer( size_t index ) const;
		size_t										getNumberServer( void ) const;
		
		/*	PRINTER	*/
		void										printServers( void ) const;
		void										printOneServer( size_t index ) const;

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