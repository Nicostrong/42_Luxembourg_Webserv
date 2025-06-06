/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/05 09:20:23 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE
# define HTTP_RESPONSE

#include "./../lib.hpp"
#include "./../utils/Buffer.hpp"
#include "./../utils/Uri.hpp"
#include "./HttpBase.hpp"
#include "./HttpParser.hpp"
#include "./HttpRequest.hpp"

class HttpResponse: public HttpParser
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
		void				setRespType(ResponseType type);
		ResponseType		getRespType() const;
	private:
		ResponseType	_respType;
};

# endif