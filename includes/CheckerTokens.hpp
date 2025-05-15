/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:23 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/15 15:11:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER
# define CHECKER

# include "lib.hpp"
# include "Token.hpp"
# include "MethodHTTP.hpp"

class	Token;

/*
 *	CheckerTokens class check the sementic off all token of the config file
 *	If the sementic isn't correct it throw an exception
 */
class	CheckerTokens
{

	private:

		Token*			_head;
		int				_braceCount;
		bool			_inServer;
		bool			_inLocation;
		bool			_inErrorBlk;
		bool			_inCGI;

		CheckerTokens( const CheckerTokens& src_obj );

		CheckerTokens	&operator=(  const CheckerTokens& src_obj );

		void			validate( void );
		void			checkCGI( void );
		void			checkpath( void );
		void			checkValue( void ) ;
		void			checkMethodHTTP( void );
		void			checkBlockError( void );
		void			checkBracesAndBlocks( void );
		void			checkHTTPKeyValuePairs( void );
		void			assertFinalState( void ) const;
		void 			checkCGITokens( Token* current );
		void			checkDuplicatedKeysInScope( void );
		void			checkDirectiveKeyValuePairs( void );
		void			checkServerTokens( Token* current );
		void			checkSemicolonBeforeBlockEnd( void );
		void			checkSemicolonAfterHTTPValue( void );
		void			checkLocationTokens( Token* current );
		void			checkErrorPageTokens( Token* current );
		void			checkSemicolonAfterDirectiveValue( void );
	
	public:

		CheckerTokens( Token* head );
		~CheckerTokens( void );

		static void		check( Token* head );
	
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