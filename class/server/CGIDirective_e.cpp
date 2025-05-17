/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIDirective_e.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:57:56 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/17 11:49:07 by nicostrong       ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/CGIDirective.hpp"

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
