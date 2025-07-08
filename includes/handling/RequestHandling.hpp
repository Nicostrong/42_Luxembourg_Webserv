/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:29:55 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLING_HPP
# define REQUESTHANDLING_HPP

# define SUPPORTED_HTTPVER "HTTP/1.1"

# include "../lib.hpp"
# include "../cgi/CGI.hpp"
# include "../utils/Uri.hpp"
# include "../server/Server.hpp"
# include "../http/HttpBase.hpp"
# include "../utils/Endpoint.hpp"
# include "../http/HttpRequest.hpp"
# include "../http/HttpResponse.hpp"

class	RequestHandling
{
	public:

		// Request handling
		static void		handleHeaders(Socket& sock);
		static void		handleBody(Socket& sock);

	private:

		typedef void		(*HandlerFunc)(Socket& sock);

		RequestHandling( void );
		RequestHandling(const RequestHandling& obj);
		~RequestHandling( void );
		
		RequestHandling&	operator=(const RequestHandling& obj);
		
		// Check response types
		static bool 		isCGI( Socket& sock );
		static bool			isRedirect( Socket& sock );
		static bool			isIndexFile( Socket& sock );
		static bool			checkCGIext( Socket& sock );
		static bool			isStaticFile( Socket& sock );
		static bool			isDirctoryListing( Socket &sock );
		static bool			ends_with( const std::string& str, const std::string& suffix );

		// Get realated
		static void			handleGet( Socket& sock );

		// Post related
		static void			handlePost( Socket& sock );
		static void			handleBodyLength( Socket& sock );
		static void			handleTE( Socket& sock );
		static void			handleContentLength( Socket& sock );
		static void			checkFileExistUpload( const std::string& path );
		static void			checkFolderExistUpload( const std::string& dir );

		// Delete related
		static void			handleDelete( Socket& sock );
		static void			checkFileExistDelete( const std::string& path );
		
		static std::map<std::string, HandlerFunc>		_handlers;

		static std::map<std::string, RequestHandling::HandlerFunc>	initHandlers();
		
		// CGI
		// CGI Variables	
		std::string data;
		// CGI Functions
		static std::string	getQueryString(const std::string& request);
		static void			setAttributes( Socket& socket );
		
};

#endif