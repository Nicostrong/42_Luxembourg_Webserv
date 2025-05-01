/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RessourcesManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:43:33 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 11:49:01 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESSOURCES_MANAGER_HPP
# define RESSOURCES_MANAGER_HPP

#include "lib.hpp"
#include "Ressource.hpp"
#include "EventMonitoring.hpp"

class RessourcesManager
{
    public:
        RessourcesManager(EventMonitoring& em);
        RessourcesManager(const RessourcesManager& obj);
        ~RessourcesManager();
        RessourcesManager&  operator=(const RessourcesManager& obj);
        Ressource::State    getRessourceState(const std::string& loc);
        Ressource*          getRessource(const std::string& loc);
        void                loadRessource(const std::string& loc);
    private:
        EventMonitoring&        _em;
        std::list<Ressource>    _ressources;
};

#endif