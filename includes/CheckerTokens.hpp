/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:23 by nicostrong        #+#    #+#             */
/*   Updated: 2025/05/11 16:54:37 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER
# define CHECKER

# include "./lib.hpp"
# include "./Token.hpp"
# include "./MethodHTTP.hpp"

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

		void			checkValue( void ) ;
		void			checkMethodHTTP( void );
;		void			checkBracesAndBlocks( void );
		void			assertFinalState( void ) const;
		void			checkDuplicatedKeysInScope( void );
		void			checkDirectiveKeyValuePairs( void );
		void			checkSemicolonBeforeBlockEnd( void );
		void			checkSemicolonAfterDirectiveValue( void );
	
	public:

		CheckerTokens( Token* head );
		~CheckerTokens( void );
	
		void			validate( void );

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