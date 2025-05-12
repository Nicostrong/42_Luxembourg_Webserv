/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/12 14:00:26 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

# include "./Server.hpp"
# include "./Token.hpp"

class	ServerManager
{

	private:

		std::map<int, Server*>      	_mServers;

		ServerManager( const ServerManager& src_obj );

		ServerManager&	operator=( const ServerManager& src_obj );

	public:

		ServerManager( const std::list<Token*>& serverListToken );
		~ServerManager( void );

		/*	GETTER	*/
		const std::map<int, Server*>&	getServers( void ) const;
		Server*							getServer( int port ) const;
	
		/*	SETTER	*/
		void							addServer( int port, Server* server );
		
};

#endif