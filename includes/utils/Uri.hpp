/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:30:28 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:42:53 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_HPP
# define URI_HPP

# include "../lib.hpp"
# include "../server/Location.hpp"
# include "../server/Directive.hpp"

class   Server;

class   Uri
{
    public:

        Uri(const Uri& obj);
        ~Uri();

        Uri& operator=(const Uri& obj);

        static std::string getCgiPath(
            const std::list<Directive*>& cgiDirectives, const Location* loc, 
            const std::string& uri);
        static std::string trimSlashBegin(const std::string& uri);
        static std::string trimSlashEnd(const std::string& uri);
        static std::string buildUri(std::string p1, std::string p2);
        static std::string getPathInfo(const Location *loc, std::string uri);
        static std::string buildByReplacingLoc(const Location* loc, 
            std::string uri, std::string replacement);
        static std::string buildRealAbsolute(const Server& serv, 
            const Location* loc, std::string uri);
        static std::string buildRealRelative(const Server& serv, 
            const Location* loc, std::string uri);

    private:

        Uri();

        static bool    isCgiExtValid(const std::list<Directive*>& cgiDirectives,
            const std::string& filename);

};

#endif