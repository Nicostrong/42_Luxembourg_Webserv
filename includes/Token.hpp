/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:56:03 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/10 17:56:47 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "./lib.hpp"
# include "./Nico.hpp"

class 	Token
{

	public:

		enum	Type
		{
			SERVER,			//	server block
			BLK_S,			//	block start
			DIR_K,			//	key directive
			DIR_V,			//	value directive
			ERR_K,			//	key error
			ERR_BLK_S,		//	block error start
			ERR_BLK_E,		//	block error end
			LOC_K,			//	location key
			LOC_BLK_S,		//	location block start
			HTTP_K,			//	HTTP key
			HTTP_V,			//	method HTTP value
			LOC_BLK_E,		//	location block end
			BLK_E,			//	block end
			BRACE_S,		//	brace open
			BRACE_E,		//	brace close
			SEMICOLON		//	end of directive
		};

		Token( Type type, const std::string& value );
		Token( const Token& src_obj );
		~Token( void );

		Token&						operator=( const Token& src_obj );

		/*	GETTER	*/
		int							getType( void ) const;
		
		std::string					getTypeName( void ) const;
		std::string					getValue( void ) const;

		Token*						getNext( void ) const;

		/*	METHOD	*/
		void						printToken( void ) const;

		static Token*				tokenize( const std::string& serverConfig );

	private:

		Type						_type;
		std::string					_value;
		Token*						_next;

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

};

#endif