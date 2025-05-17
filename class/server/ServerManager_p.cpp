/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_p.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:13:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:52:27 by nicostrong       ###   Luxembourg.lu     */
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
	std::list<Token*>::iterator		it;
#ifdef DEBUG
	for (it = this->_lServerToken.begin(); it != this->_lServerToken.end(); it++)
	{
		std::cout << "PRINT TOKEN LIST" << std::endl;
		(*it)->printToken();
	}
#endif
	return ;
}