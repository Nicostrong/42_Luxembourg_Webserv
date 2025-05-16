/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 17:16:17 by nicostrong       ###   Luxembourg.lu     */
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

		std::map<size_t, std::vector<Server*> >		_mServers;
		std::set<Server*>							_sServers;
		std::list<Token*>							_lServerToken;
		int											_nbServer;

		ServerManager( const ServerManager& src_obj );

		ServerManager&		operator=( const ServerManager& src_obj );

		void		splitServerToken( Token *head );

	public:

		ServerManager( Token* allTokens, EventMonitoring& eventMonitoring );
		~ServerManager( void );

		/*	GETTER	*/
		Server*			getServer( size_t port, std::string host ) const;

		const std::set<Server*>&		getAllServers( void ) const;

		std::vector<Server*>		getAllServersForPort( size_t port ) const;

		int				getNbServer( void ) const;

		/*	Method	*/
		void		startAll( void );

		bool		isValidPort( size_t port ) const;
				
};

#endif