/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:11 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 17:50:40 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseHandling.hpp"

ResponseHandling::ResponseHandling() {}

ResponseHandling::ResponseHandling(const ResponseHandling& obj) 
{
    (void)obj;
}

ResponseHandling::~ResponseHandling() {}

ResponseHandling& ResponseHandling::operator=(const ResponseHandling& obj)
{
    (void)obj;
    return (*this);
}
       