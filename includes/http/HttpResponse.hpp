/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/20 09:11:35 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE
# define HTTP_RESPONSE

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../utils/Uri.hpp"
#include "./HttpBase.hpp"
#include "./HttpRequest.hpp"

class HttpResponse: public HttpBase
{
	public:
		enum ResponseType
		{
			UNKNOWN = 0,
			STATIC_FILE = 1,
			CGI = 2,
			REDIRECT = 3,
			DIRECTORY_LISTING = 4,
			ERROR = 5,
		};
		HttpResponse();
		HttpResponse(const HttpResponse& obj);
		virtual ~HttpResponse();
		HttpResponse&		operator=(const HttpResponse& obj);
		
		void				sendHead(Buffer& buff);
		void 				sendDefaultErrorPage(Buffer& buff);	
		void				sendDirectoryListing(Buffer& buff, 
			const HttpRequest& req);
		void				setStatusStr(const std::string& statusStr);
		void				setRespType(ResponseType type);
		ResponseType		getRespType() const;
		void				encodeHead(const std::string data);
	private:
		ResponseType	_respType;
		Buffer			_headBuffer;
		
		std::string		_statusStr;
		
};

# endif
