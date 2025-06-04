/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testvectorexecve.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:28:33 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/04 16:39:17 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <string>

extern char **environ;

int main()
{
    std::vector<std::string> cmd_list_vector;
    std::vector<const char *> cmd_list;
    cmd_list_vector.push_back("/bin/echo");
    cmd_list_vector.push_back("hello");
    cmd_list_vector.push_back(NULL);
    for(std::vector<std::string>::iterator it = cmd_list_vector.begin(); it != cmd_list_vector.end(); ++it)
    {
        cmd_list.push_back(it->c_str());
    }
    execve(cmd_list[0], &cmd_list[0], environ);
}