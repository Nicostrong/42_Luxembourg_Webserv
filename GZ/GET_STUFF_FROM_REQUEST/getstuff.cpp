/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstuff.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:35:09 by gzenner           #+#    #+#             */
/*   Updated: 2025/06/05 09:54:11 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

// this goes somewhere before CGI and gets us the string to pass to CGI
void getStuff(std::string& request, std::string& data)
{
    if (request.find("?") != std::string::npos)
    {
        request = request.substr(request.find("?") + 1);
        //std::cout << "[debug request]" << request << "\n";
        data = request.substr(0, request.find_first_of(" \t"));
        //std::cout << "[debug data]" << data << ".\n";
    }
}

//Function goes into CGI - splits the string into map values
void string_to_map(std::string& data, std::map<std::string, std::string>& datamap)
{
    std::string tmp = data;
    while(tmp.find("&") != std::string::npos)
    {
        std::string snippet = tmp.substr(0, tmp.find("&"));
        std::cout << "[debug snippet]" << snippet << "\n";
        tmp = tmp.substr(tmp.find("&") + 1);
        std::string key = snippet.substr(0, snippet.find("="));
        std::cout << "[debug key]" << key << ".\n";
        std::string value = snippet.substr(snippet.find("=") + 1);
        std::cout << "[debug value]" << value << ".\n";
        datamap[key] = value;
    }
}

int main()
{
    std::string request = "GET /cgi-bin/adduser.html/?name=Alice&age=30";
    std::string data;
    std::map<std::string, std::string> datamap;
    getStuff(request, data);
    string_to_map(data, datamap);
    return (0);
}