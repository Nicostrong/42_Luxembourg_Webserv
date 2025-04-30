/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:30:19 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/30 12:54:38 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequests.hpp"

int main(void)
{
	EventMonitoring em;
	HandleRequests hr(em);
	return 0;
}