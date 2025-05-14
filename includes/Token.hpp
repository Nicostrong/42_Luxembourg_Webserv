/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:56:03 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/14 15:13:28 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "./lib.hpp"
# include "./ParserServerConfig.hpp"

/*
 *	Token class is to tokenize the server configuration file.
 *	Each token is a part of the configuration file, like a key, a value, a brace
 *	or a semicolon.
 */
class 	Token
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
			HTTP_K,			//	HTTP key
			HTTP_V,			//	method HTTP value
			DIR_K,			//	key directive
			DIR_V,			//	value directive
			CGI_V,			//	CGI path
			SEMICOLON		//	end of directive
		};

		Token( Type type, const std::string& value );
		~Token( void );

		/*	GETTER	*/
		int							getType( void ) const;
		
		std::string					getTypeName( void ) const;
		std::string					getValue( void ) const;

		Token*						getNext( void ) const;

		/*	SETTER	*/
		void						setNextToNull( void  );

		/*	METHOD	*/
		void						printToken( bool isNext = false ) const;

		static Token*				tokenize( const std::string& serverConfig );

	private:

		Type						_type;
		std::string					_value;
		Token*						_next;

		Token( const Token& src_obj );

		Token&						operator=( const Token& src_obj );
		
		/*	PRIVATE METHODS	*/
		static void					attachToken(	Token*& head,
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
		static Token*				createBrace(	const std::string& word,
													Token*& head,
													Token*& current,
													int& braceCount,
													bool& inLocation,
													bool& inErrorBlk,
													bool& inServer);
		static Token*				createSemicolon(	const std::string& word,
														Token*& head,
														Token*& current,
														bool& inHTTP);
		static Token*				createDirective(	std::istringstream& iss,
														const std::string& word,
														Token*& head,
														Token*& current);
		static Token*				createLocation( std::istringstream& iss,
													Token*& head,
													Token*& current,
													int& braceCount,
													bool& inLocation );
		static Token*				createCGIDirective(	std::istringstream& iss,
														Token*& head, 
														Token*& current,
														int& braceCount,
														bool& inCGI );

};

#endif