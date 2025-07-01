/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/01 18:08:39 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_STATE_HPP
# define PROCESS_STATE_HPP

class ProcessState
{
    public:
        static void setChild();
        static bool getChild();
    private:
        ProcessState();
        ProcessState(ProcessState& obj);
        ~ProcessState();
        ProcessState& operator=(const ProcessState& obj);

        static bool isChild;
};

# endif