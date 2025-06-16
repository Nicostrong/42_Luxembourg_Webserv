/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandling.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:12:54 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/06 10:02:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLING_HPP
# define CGIHANDLING_HPP

#include "./lib.hpp"

class CgiHandling
{
    public:
    private:
        CgiHandling();
        CgiHandling(const CgiHandling& obj);
        ~CgiHandling();
        CgiHandling& operator=(const CgiHandling& obj);
		void		handleHeaders();

        static bool isStatusHeaderValid(const std::string& status);
        static bool isLocationValid(const std::string& loc);
};

#endif