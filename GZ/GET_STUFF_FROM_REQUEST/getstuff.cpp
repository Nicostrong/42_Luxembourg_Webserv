/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstuff.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:35:09 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/05 13:48:14 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

// this goes somewhere before CGI and gets us the string to pass to CGI
void getQueryString(std::string& request, std::string& data)
{
    if (request.find("?") != std::string::npos)
    {
        request = request.substr(request.find("?") + 1);
        data = request.substr(0, request.find_first_of(" \t"));
    }
}

//Function goes into CGI - splits the string into map values
void string_to_map(std::string& data, std::map<std::string, std::string>& datamap)
{
    std::string tmp = data;
    while(tmp.find("&") != std::string::npos)
    {
        std::string snippet = tmp.substr(0, tmp.find("&"));
        tmp = tmp.substr(tmp.find("&") + 1);
        std::string key = snippet.substr(0, snippet.find("="));
        std::string value = snippet.substr(snippet.find("=") + 1);
        datamap[key] = value;
    }
    std::string snippet = tmp.substr(0, tmp.find("&"));
    std::string key = snippet.substr(0, snippet.find("="));
    std::string value = snippet.substr(snippet.find("=") + 1);
    datamap[key] = value;
}

char const** map_to_chartab(std::map<std::string, std::string>& datamap)
{
    size_t i = 0;
    char const** newenviron = (char const**)malloc(datamap.size() * sizeof(char const*) * 2);
    for (std::map<std::string, std::string>::iterator it = datamap.begin(); it != datamap.end(); ++it)
    {
        newenviron[i++] = it->first.c_str();
        newenviron[i++] = it->second.c_str();
        std::cout << "[debug key]" << newenviron[i-2] << ":";
        std::cout << "[debug value]" << newenviron[i-1] << ".\n";
    }
    return (newenviron);
}

int main()
{
    std::string request = "GET /cgi-bin/adduser.html/?name=Alice&age=30&height=1.80&width=.8&eye-color=brown";
    std::string data;
    std::map<std::string, std::string> datamap;
    getQueryString(request, data);
    string_to_map(data, datamap);
    char const** newenviron = map_to_chartab(datamap);
    free(newenviron);
    return (0);
}