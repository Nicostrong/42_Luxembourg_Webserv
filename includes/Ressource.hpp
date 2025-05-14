/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:45:19 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/09 07:09:22 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESSOURCE_HPP
# define RESSOURCE_HPP

#include "lib.hpp"
#include "IEventHandler.hpp"

#define RESSOURCE_BUFFER_SIZE 1024

class Ressource
{
	public:
		Ressource(const std::string loc);
		Ressource(const Ressource& obj);
		~Ressource();
		Ressource&			operator=(const Ressource& obj);
		const std::string&	getLoc() const;
		const std::string&	getRaw() const;
		bool				isFail() const;

	private:
		std::string	_loc;
		std::string	_raw;
		bool		_isFail;
};

#endif