/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_p.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:13:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 13:35:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/ServerManager.hpp"

/*******************************************************************************
 *							PRIVATE METHOD									   *
 ******************************************************************************/

/*
 *	Split the Tokens list to separate each server config
 */
void			ServerManager::splitServerToken( Token *head )
{
	while (head)
	{
		if (head->getType() == Token::SERVER)
		{
			Token*		server = head;
			Token*		tmp = head;

			while (tmp && tmp->getType() != Token::SER_BLK_E)
				tmp = tmp->getNext();
			if (tmp)
			{
				head = tmp->getNext();
				tmp->setNextToNull();
				this->_lServerToken.push_back(server);
			}
		}
		else
			head = head->getNext();
	}
#ifdef DEBUG
	std::list<Token*>::iterator		it;
	for (it = this->_lServerToken.begin(); it != this->_lServerToken.end(); it++)
	{
		LOG_DEB("PRINT TOKEN LIST");
		(*it)->printToken();
	}
#endif
	return ;
}

/*
 *	Clean all ressources of the object ServerManager
 */
void		ServerManager::cleanRessources( void )
{
	std::set<Server*>::iterator		itSer;
	std::list<Token*>::iterator		itTok;

	for (itSer = this->_sServers.begin(); itSer != this->_sServers.end(); ++itSer)
		delete *itSer;

	for (itTok = this->_lServerToken.begin(); itTok != this->_lServerToken.end(); ++itTok)
		(*itTok)->deleteList();
	
	this->_mServers.clear();
	this->_sServers.clear();
	this->_lServerToken.clear();
	return ;
}