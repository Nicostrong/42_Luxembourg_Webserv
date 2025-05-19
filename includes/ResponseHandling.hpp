/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHandling.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:26 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 18:36:25 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHANDLING_HPP
#define RESPONSEHANDLING_HPP

class ResponseHandling
{
    public:
        ResponseHandling(const ResponseHandling& obj);
        ~ResponseHandling();
        ResponseHandling& operator=(const ResponseHandling& obj);
    private:
        ResponseHandling();
        
};

#endif