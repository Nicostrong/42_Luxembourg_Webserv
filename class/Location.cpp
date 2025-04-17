/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:28:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 12:06:27 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
Location::Location( std::map<std::string, std::string> &data )
{
	std::string										key;
	std::string										value;
	std::map<std::string, std::string>::iterator	it;

	if (data.count("location") == 0 || data.empty())
		return ;
	
	it = data.begin();
	key = it->first;
	value = it->second;

	return ;
}

void	Location::parseValue( const std::string &data, std::string &key, std::string &value )
{
	size_t firstBrace = input.find('{');

	if (firstBrace == std::string::npos)
	{
		value_1 = input;
		value_2 = "";
		return;
	}

	value_1 = input.substr(0, firstBrace);
	size_t firstClosingBrace = input.find('}', firstBrace);
	if (firstClosingBrace == std::string::npos)
	{
		value_2 = ""; // Aucun '}' trouvé
		return;
	}

	value_2 = input.substr(firstBrace + 1, firstClosingBrace - firstBrace - 1);
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error creating server
 */
const char		*Location::LocationException::what() const throw()
{
	return  (RED"Error location !"RESET);
}

/*******************************************************************************
 *								OUTSTREAM									   *
 ******************************************************************************/

/*
 *	output stream operator
 */
std::ostream	&operator<<( std::ostream &out, Location const &src_object )
{
	out	<< GREEN << "LOCATION INFORMATION"
		<< RESET;
	return (out);
}