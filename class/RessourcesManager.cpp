/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RessourcesManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:43:22 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 13:41:30 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RessourcesManager.hpp"

RessourcesManager::RessourcesManager(EventMonitoring& em) : _em(em) {}

RessourcesManager::RessourcesManager(const RessourcesManager& obj) : 
    _em(obj._em), _ressources(obj._ressources) {}

RessourcesManager::~RessourcesManager() {}

RessourcesManager& RessourcesManager::operator=(const RessourcesManager& obj) 
{
    if (this != &obj)
    {
        this->_em = obj._em;
        this->_ressources = obj._ressources;
    }
    return (*this);
}

Ressource::State RessourcesManager::getRessourceState(const std::string& loc)
{
    std::list<Ressource>::const_iterator it = this->_ressources.begin();
    while (it != this->_ressources.end())
    {
        if (it->getLoc() == loc)
            return (it->getState());
        ++it;
    }
    return (Ressource::NOT_EXISTING);
}

Ressource* RessourcesManager::getRessource(const std::string& loc)
{
    std::list<Ressource>::iterator it = this->_ressources.begin();
    while (it != this->_ressources.end())
    {
        if (it->getLoc() == loc)
            return (&(*it));
        ++it;
    }
    return (NULL);
}

void RessourcesManager::loadRessource(const std::string& loc)
{
    if (getRessourceState(loc) == Ressource::NOT_EXISTING )
    {
        Ressource ressource(loc, this->_em);
        this->_ressources.push_front(ressource);
    }
}