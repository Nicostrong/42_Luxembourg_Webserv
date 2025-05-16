/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager_p.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:13:20 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 16:14:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ServerManager.hpp"

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
				this->_serverToken.push_back(server);
			}
		}
		else
			head = head->getNext();
	}
	std::list<Token*>::iterator		it;
#ifdef DEBUG
	for (it = this->_serverToken.begin(); it != this->_serverToken.end(); it++)
	{
		std::cout << "PRINT TOKEN LIST" << std::endl;
		(*it)->printToken();
	}
#endif
	return ;
}