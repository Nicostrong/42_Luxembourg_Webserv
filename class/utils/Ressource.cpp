/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ressource.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:51:46 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:13:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils/Ressource.hpp"

Ressource::Ressource(const std::string loc) : _loc(loc), _raw(), _isFail(false)
{
	
	std::ifstream res(loc.c_str());
	std::stringstream resStream;

	if (!res || !res.is_open()) 
	{
		this->_isFail = true;
		return ;
	}
	
	resStream << res.rdbuf();
	
	if (res.bad()) 
	{
		this->_isFail = true;
		res.close();
		return ;
	}
	
	res.close();
	this->_raw = resStream.str();
}

Ressource::Ressource(const Ressource& obj) 
{
	*this = obj;
}

Ressource::~Ressource() {}

Ressource& Ressource::operator=(const Ressource& obj)
{
	if (this != &obj)
	{
		this->_loc = obj._loc;
		this->_raw = obj._raw;
		this->_isFail = obj._isFail;
	}
	return (*this);
}

const std::string&	Ressource::getLoc() const
{
	return (this->_loc);
}

const std::string& Ressource::getRaw() const
{
	return (this->_raw);
}

bool Ressource::isFail() const
{
	return (this->_isFail);
}
