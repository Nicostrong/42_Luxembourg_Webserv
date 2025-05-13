/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:23 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/13 15:19:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER
# define CHECKER

# include "./lib.hpp"
# include "./MethodHTTP.hpp"

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

		CheckerTokens( const CheckerTokens& src_obj );

		CheckerTokens	&operator=(  const CheckerTokens& src_obj );

		void			validate( void );
		void			checkValue( void ) ;
		void			checkMethodHTTP( void );
		void			checkBracesAndBlocks( void );
		void			assertFinalState( void ) const;
		void			checkDuplicatedKeysInScope( void );
		void			checkDirectiveKeyValuePairs( void );
		void			checkSemicolonBeforeBlockEnd( void );
		void			checkSemicolonAfterHTTPValue( void );
		void			checkSemicolonAfterDirectiveValue( void );
	
	public:

		CheckerTokens( Token* head );
		~CheckerTokens( void );

		static void		check( Token* head );
	
		/*	checkererror Exception	*/
		class	CheckerError: public std::exception
		{
			private:
				std::string				_msg;
			public:
				CheckerError( const std::string& data ) throw();
				virtual ~CheckerError( void ) throw();
				virtual const char	*what() const throw();
		
		};
		
};

#endif