/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstuff.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:35:09 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/05 14:36:24 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <cstring>
#include <string>

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

char * const* map_to_chartab(std::map<std::string, std::string>& datamap)
{
    size_t i;
    char **newenviron;

    i = 0;
    newenviron = new char*[datamap.size() * 4 + 1];
    for (std::map<std::string, std::string>::iterator it = datamap.begin(); it != datamap.end(); ++it)
    {
        newenviron[i++] = strdup(it->first.c_str());
        newenviron[i++] = strdup(";");
        newenviron[i++] = strdup(it->second.c_str());
        newenviron[i++] = strdup(";");
    }
    newenviron[i] = NULL;
    return (newenviron);
}

void initEnvironMapNULL()
{
    std::map<std::string, std::string> environmap;
    environmap["AUTH_TYPE"] = "NULL";
    environmap["CONTENT_LENGTH"] = "NULL";
    environmap["CONTENT_TYPE"] = "NULL";
    environmap["GATEWAY_INTERFACE"] = "NULL";
    environmap["PATH_INFO"] = "NULL";
    environmap["PATH_TRANSLATED"] = "NULL";
    environmap["QUERY_STRING"] = "NULL";
    environmap["REMOTE_ADDR"] = "NULL";
    environmap["REMOTE_HOST"] = "NULL";
    environmap["REMOTE_IDENT"] = "NULL";
    environmap["REMOTE_USER"] = "NULL";
    environmap["SCRIPT_NAME"] = "NULL";
    environmap["SERVER_NAME"] = "NULL";
    environmap["SERVER_PORT"] = "NULL";
    environmap["SERVER_PROTOCOL"] = "NULL";
    environmap["SERVER_SOFTWARE"] = "NULL";
}

int main()
{
    initEnvironMapNULL();
    
    std::string request = "GET /cgi-bin/adduser.html/?name=Alice&age=30&height=1.80&width=.8&eye-color=brown";
    std::string data;
    std::map<std::string, std::string> datamap;
    getQueryString(request, data);
    string_to_map(data, datamap);
    char * const* newenviron = map_to_chartab(datamap);
    size_t i = 0;
    while(newenviron[i])
    {
        std::cout << "[debug]" << newenviron[i++] << "\n";
    }
    delete[](newenviron);
    return (0);
}