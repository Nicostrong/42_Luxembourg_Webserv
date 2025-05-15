/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/15 10:34:40 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

# include "Server.hpp"

class	Token;

/*
 *	The ServerManager object is a container for all the server objects.
 *	It is used to manage the server objects and to get the server object
 *	by its port.
 */
class	ServerManager
{

	private:

		std::map<int, Server*>				_mServers;
		int									_nbServer;

		ServerManager( const ServerManager& src_obj );

		ServerManager&		operator=( const ServerManager& src_obj );

	public:

		ServerManager( const std::list<Token*>& serverListToken,
						EventMonitoring& eventMonitoring );
		~ServerManager( void );

		/*	GETTER	*/
		const std::map<int, Server*>&		getServers( void ) const;
		
		Server*								getServer( int port ) const;

		int									getNbServer( void ) const;

		/*	Method	*/
		void								startAll( void );
				
};

#endif