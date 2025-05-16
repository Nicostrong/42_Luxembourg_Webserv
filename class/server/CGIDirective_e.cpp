/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective_e.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:57:56 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:58:16 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGIDirective.hpp"

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Error fields empty
 */
const char*     CGIDirective::FieldsEmpty::what() const throw()
{
	return  (RED "[ERROR CGI] Fields of CGIDirective object empty !" RESET);
}

/*
 *	Bad token type
 */
const char*     CGIDirective::BadTokenType::what() const throw()
{
	return  (RED "[ERROR CGI] Bad token type for creating CGIDirective !" RESET);
}
