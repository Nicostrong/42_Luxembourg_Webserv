/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nico.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/29 21:06:21 by nfordoxc         ###   Luxembourg.lu     */
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
		ParserServerConfig( const ParserServerConfig &src );
		ParserServerConfig &operator=( const ParserServerConfig &src );

		int				parsePort( const std::string &value );

		void			parseServerBlock( const std::string &block );
		void			parseConfigFile( const std::string &filename );

		size_t			countChar( const std::string &str, char c );

		std::string		trim( const std::string &s );
		std::string		extractBlock( std::istringstream &iss );
		std::string		stripComments( const std::string &line );

	public:

		ParserServerConfig( const std::string &filename );
		~ParserServerConfig( void );

		/*	GETTER	*/
		const std::map<std::string, std::string>		&getServers( void ) const;
		void											printServers( void ) const;
		
};


#endif