/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/10 18:39:25 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLING_HPP
# define REQUESTHANDLING_HPP

#define SUPPORTED_HTTPVER "HTTP/1.1"

# include "./../lib.hpp"
# include "./../utils/Uri.hpp"
# include "./../utils/Endpoint.hpp"
# include "./../http/HttpBase.hpp"
# include "./../http/HttpRequest.hpp"
# include "./../http/HttpResponse.hpp"
# include "./../server/Server.hpp"
# include "./HandleCGI.hpp"

class RequestHandling: public HttpBase
{
	public:
		// Request handling
		static void	handleHeaders(Socket& sock);
		static void handleBody(Socket& sock);
	private:
		typedef void (*HandlerFunc)(Socket& sock);
		RequestHandling();
		RequestHandling(const RequestHandling& obj);
		~RequestHandling();
		RequestHandling&	operator=(const RequestHandling& obj);
		
		// Check response types
		static bool 		isCGI(Socket& sock);
		static bool			isRedirect(Socket& sock);
		static bool			isIndexFile(Socket& sock);
		static bool			isDirctoryListing(Socket &sock);
		static bool			isStaticFile(Socket& sock);
		static bool			ends_with( const std::string& str, const std::string& suffix );

		// Get realated
		static void			handleGet(Socket& sock);

		// Post related
		static void			handlePost(Socket& sock);
		static void			handleBodyLength(Socket& sock);
		static void			handleTE(Socket& sock);
		static void			handleContentLength(Socket& sock);
		static void			checkFileExistUpload(const std::string& path);
		static void			checkFolderExistUpload(const std::string& dir);

		// Delete related
		static void			handleDelete(Socket& sock);
		static void			checkFileExistDelete(const std::string& path);
		
		static std::map<std::string, HandlerFunc> _handlers;

		static std::map<std::string, RequestHandling::HandlerFunc> 
			initHandlers();
		
		// CGI
		// CGI Variables	
		std::string data;
		// CGI Functions
		static std::string getQueryString(const std::string& request);
};

#endif