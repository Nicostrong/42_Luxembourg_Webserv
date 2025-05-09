/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:56:03 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/09 18:05:06 by nfordoxc         ###   Luxembourg.lu     */
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
		std::string					getType( void ) const;
		std::string					getValue( void ) const;

		Token*						getNext( void ) const;

		/*	METHOD	*/
		void						printToken( void ) const;

		Token*						tokenize( const std::string& serverConfig );

	private:

		Type						_type;
		std::string					_value;
		Token*						_next;

		/*	PRIVATE METHODS	*/
		void						attachToken(	Token*& head,
													Token*& current,
													Token* newToken );

		bool						isDirectiveKey( const std::string& word );

		Token*						createErrorPage(	std::istringstream& iss,
														std::string word,
														Token*& head,
														Token*& current,
														int& braceCount,
														bool& inErrorBlk );
		Token*						createBrace(	const std::string& word,
													Token*& head,
													Token*& current,
													int& braceCount,
													bool& inLocation,
													bool& inErrorBlk,
													bool& inServer);
		Token*						createSemicolon(	const std::string& word,
														Token*& head,
														Token*& current,
														bool& inHTTP);
		Token*						createDirective(	std::istringstream& iss,
														const std::string& word,
														Token*& head,
														Token*& current);
		Token*						createLocation( std::istringstream& iss,
													Token*& head,
													Token*& current,
													int& braceCount,
													bool& inLocation );

};

#endif