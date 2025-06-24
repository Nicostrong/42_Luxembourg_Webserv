/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:23 by nicostrong        #+#    #+#             */
/*   Updated: 2025/06/24 16:22:55 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER
# define CHECKER

# include "../lib.hpp"
# include "../parser/Token.hpp"
# include "../server/MethodHTTP.hpp"

class	Token;

/*
 *	CheckerTokens class check the sementic off all token of the config file
 *	If the sementic isn't correct it throw an exception
 */
class	CheckerTokens
{

	private:

		const Token*		_head;
		int					_braceCount;
		bool				_inServer;
		bool				_inLocation;
		bool				_inErrorBlk;
		bool				_inCGI;

		CheckerTokens( const CheckerTokens& src_obj );

		CheckerTokens		&operator=(  const CheckerTokens& src_obj );
		
		void				checkpath( void );
		void				checkValue( void );
		void				checkListen( void );
		void				checkReturn( void );
		void				checkUniqValue( void );
		void				validateTokens( void );
		void				checkMethodHTTP( void );
		void				checkBracesAndBlocks( void );
		void				checkHTTPKeyValuePairs( void );
		void				assertFinalState( void ) const;
		void				checkUnexpectedSemicolons( void) ;
		void				checkDuplicatedKeysInScope( void );
		void				checkDirectiveKeyValuePairs( void );
		void				checkSemicolonBeforeBlockEnd( void );
		void				checkSemicolonAfterHTTPValue( void );
		void 				checkCGITokens( const Token* current );
		void				checkSemicolonAfterDirectiveValue( void );
		void				checkServerTokens( const Token* current );
		void				checkLocationTokens( const Token* current );
		void				checkErrorPageTokens( const Token* current );

		bool				validCode( std::string code );
		bool				is_valid_dir( const std::string& path );
		bool				is_valid_file( const std::string& path );
		bool				is_executable_file( const std::string& path );

		void				validate_root( const Token* current );
		void				validate_index( const Token* current );
		void				validate_return( const Token* current );
		void				validate_location( const Token* current );

		const Token*		validate_error_block( const Token* current );

	
	public:

		CheckerTokens( const Token& head );
		~CheckerTokens( void );

		static void			check( const Token& head );
	
		/*	EXCEPTION	*/

		/*	checkererror Exception	*/
		class	CheckerError: public std::exception
		{
			private:
				std::string				_msg;
			public:
				CheckerError( const std::string& data ) throw();
				virtual ~CheckerError( void ) throw();
				virtual const char*		what() const throw();
		
		};
		
};

#endif