/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 10:59:50 by nfordoxc         ###   Luxembourg.lu     */
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

		std::map<size_t, Server*>				_mServers;
		std::set<Server*>						_servers;
		int										_nbServer;

		ServerManager( const ServerManager& src_obj );

		ServerManager&		operator=( const ServerManager& src_obj );

	public:

		ServerManager( const std::list<Token*>& serverListToken,
						EventMonitoring& eventMonitoring );
		~ServerManager( void );

		/*	GETTER	*/
		const std::map<size_t, Server*>&		getServers( void ) const;
		
		Server*									getServer( size_t port ) const;

		int										getNbServer( void ) const;

		/*	Method	*/
		void									startAll( void );

		bool									isValidPort( size_t port ) const;
				
};

#endif