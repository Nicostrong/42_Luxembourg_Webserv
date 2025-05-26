/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/26 11:03:41 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

# include "../server/Server.hpp"

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

		ServerManager( Token* allTokens, EventMonitoring& eventMonitoring, MemoryPool& memPool );
		~ServerManager( void );

		/*	GETTER	*/
		/*	retourne le server qui correspond au hostname et port	*/
		const Server*			getServer( size_t port, std::string host ) const;
		/*	retourne la loction correspondant a l uri	*/
		const Location*			getLocationForUri( const Server* server, const std::string& uri ) const;
		/*	retourne la taille maxi du body	*/
		size_t					getMaxBodySize( const Server* server, const Location* location ) const;
		/*	retourne la racine de fichier pour la location	*/
		std::string				getRoot( const Location* location ) const;
		/*	retourne le fichier d index	*/
		std::string				getIndexFile( const Location* location ) const;

		/*	CHECKER	*/
		/*	check si methode autorise dans la location	*/
		bool					isMethodAllowed( const Location* location, const std::string& method ) const;
		/*	check si le chemin existe */
		bool					doesPathExist( const std::string& path ) const;
		/*	check si le body est trop grand	*/
		bool					isBodyTooLarge( size_t bodySize, size_t maxSize ) const;
		/*	check si on doit afficher la liste des fichier du repertoir ou pas	*/
		bool					isAutoIndexEnabled( const Location* location ) const;

		const std::set<Server*>&		getAllServers( void ) const;

		std::vector<Server*>		getAllServersForPort( size_t port ) const;

		int				getNbServer( void ) const;

		/*	Method	*/
		void		startAll( void );

		bool		isValidPort( size_t port ) const;
				
};

#endif