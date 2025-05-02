/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/02 11:31:21 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef N
# define N

# include "./lib.hpp"

class ParserServerConfig
{

	private:

		std::map<int, std::map<std::string, std::string> >		_servers;

		ParserServerConfig( void );
		ParserServerConfig( const ParserServerConfig& src );
		ParserServerConfig&	operator=( const ParserServerConfig& src );

		int					parsePort( const std::string& value );

		bool				requireSemicolon( const std::string& line );

		void				checkHiddenFile( const std::string& filename );
		void				parseServerBlock( const std::string& block );
		void				parseConfigFile( const std::string& filename );

		size_t				countChar( const std::string& str, char c );

		std::string			trim( const std::string& s );
		std::string			extractBlock( std::istringstream& iss );
		std::string			stripComments( const std::string& line );
		std::string			copyFileToString( const std::string& filename );

	public:

		ParserServerConfig( const std::string& filename );
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