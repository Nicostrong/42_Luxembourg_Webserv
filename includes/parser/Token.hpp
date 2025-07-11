/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:56:03 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 12:29:42 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "../lib.hpp"

/*
 *	Token class is to tokenize the server configuration file.
 *	Each token is a part of the configuration file, like a key, a value, a brace
 *	or a semicolon.
 */
class	Token
{

	public:

		enum	Type
		{
			SERVER,			//	server key
			SER_BLK_S,		//	block server start
			SER_BLK_E,		//	block server end
			ERROR_PAGE,		//	key error_page
			ERR_BLK_S,		//	block error start
			ERR_BLK_E,		//	block error end
			LOCATION,		//	location key
			LOC_BLK_S,		//	location block start
			LOC_BLK_E,		//	location block end
			CGI,			//	CGI directive
			CGI_BLK_S,		//	CGI block start
			CGI_BLK_E,		//	CGI block end
			CGI_K,			//	CGI extension
			CGI_V,			//	CGI path
			HTTP_K,			//	HTTP key
			HTTP_V,			//	method HTTP value
			DIR_K,			//	key directive
			DIR_V,			//	value directive
			SEMICOLON		//	end of directive
		};

		Token( Type type, const std::string& value );
		~Token( void );

		/*	GETTER	*/
		int							getType( void ) const;
		static int					getNbServer( void );
		
		std::string					getTypeName( void ) const;
		std::string					getValue( void ) const;

		Token*						getNext( void ) const;

		/*	SETTER	*/
		static void					incServer( void );
		static void					setNbServer( void );
		void						setNextToNull( void  );

		/*	METHOD	*/
		void						deleteList( void );
		void						printToken( bool isNext = false ) const;

		static Token*				tokenize( const std::string& serverConfig );

		/*	EXCEPTION	*/
		class	TokenError: public std::exception
		{
			private:
				std::string			_msg;
			public:
				TokenError( const std::string& data ) throw();
				virtual ~TokenError( void ) throw();
				virtual const char	*what() const throw();
		
		};
		
		/*	port value error Exception	*/
		class	PortValueException : public std::exception
		{
			public:
				const char*		what() const throw();
		};

	private:

		Type						_type;
		std::string					_value;
		Token*						_next;
		static int					_nbServer;

		Token( const Token& src_obj );

		Token&						operator=( const Token& src_obj );

		static const std::string	directiveKeys[9];
		
		/*	PRIVATE METHODS	*/
		static void					attachToken(		Token*& head,
														Token*& current,
														Token* newToken );
		static void					deleteChain( Token* head );

		static bool					isDirectiveKey( const std::string& word );

		static Token*				createErrorPage(	std::istringstream& iss,
														std::string word,
														Token*& head,
														Token*& current,
														int& braceCount,
														bool& inErrorBlk );
		static Token*				createBrace(		const std::string& word,
														Token*& head,
														Token*& current,
														int& braceCount,
														bool& inLocation,
														bool& inErrorBlk,
														bool& inServer );
		static Token*				createSemicolon(	const std::string& word,
														Token*& head,
														Token*& current,
														bool& inHTTP );
		static Token*				createDirective(	std::istringstream& iss,
														const std::string& word,
														Token*& head,
														Token*& current );
		static Token*				createLocation( 	std::istringstream& iss,
														Token*& head,
														Token*& current,
														int& braceCount,
														bool& inLocation );
		static Token*				createCGIDirective(	std::istringstream& iss,
														const std::string& word,
														Token*& head, 
														Token*& current );

};

#endif