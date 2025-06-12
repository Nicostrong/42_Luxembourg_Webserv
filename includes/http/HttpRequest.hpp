/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/12 08:30:45 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "./../lib.hpp"
#include "./../server/Server.hpp"
#include "./../server/Location.hpp"
#include "./../networking/Body.hpp"
#include "./HttpBase.hpp"

class HttpRequest : public HttpBase
{
	public:

		HttpRequest( void );
		HttpRequest( const std::string& remoteIp );
		HttpRequest( const HttpRequest &obj );
		virtual~HttpRequest( void );

		HttpRequest&		operator=( const HttpRequest &obj );

		void				readReceived( int clientSocket );
		void				setLoc( const Location* const loc );
		void				setPathTranslated( const std::string& pathTranslated );
		void				setPathInfo( const std::string& pathInfo );
		void				setCgiScript( const std::string& cgiScript );
		void				setCgiPath( const std::string& cgiPath );
		void				setRedirect( const std::string& redirect );
		void				setFilePath( const std::string& filePath );
		void				setQueryParams( const std::string& queryParams );
		void				setFileSize( size_t fileSize );
		void				setContentLength( size_t length );
		void				setTE( bool state );
		void				setServer( const Server& server );
		const std::string&	getRemotIp( void ) const;
		const Location* 	getLoc( void ) const;
		const std::string&	getPathTranslated( void ) const;
		const std::string&	getPathInfo( void ) const;
		const std::string&	getCgiScript( void ) const;
		const std::string&	getCgiPath( void ) const;
		const std::string&	getRedirect( void ) const;
		const std::string&	getFilePath( void ) const;
		const std::string&	getQueryParams( void ) const;
		size_t				getFileSize( void ) const;
		size_t				getContentLength( void ) const;
		const Server*		getServer( void ) const;
		bool				isTE( void ) const;
		
	private:
	
		// Handling variables
		std::string			_remoteIp;

		// handling
		const Location*		_loc;
		std::string			_pathTranslated;
		std::string			_pathInfo;
		std::string			_cgiScript;
		std::string			_cgiPath;
		std::string			_redirect;
		std::string			_filePath;
		std::string			_queryParams;
		size_t				_fileSize;

		//Request Body
		bool				_isTE;
		size_t				_contentLength;

		// Server config
		const Server*		_server;
		
		Body*			_body;
};

std::ostream	&operator<<( std::ostream &out, const HttpRequest& src_object );

#endif