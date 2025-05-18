/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/18 20:27:24 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE
# define HTTP_RESPONSE

#include "./lib.hpp"
#include "./HttpBase.hpp"
#include "./HttpParser.hpp"
#include "./HttpRequest.hpp"
#include "./core/chunking/Encoding.hpp"

class HttpResponse: public HttpParser
{
	public:
		enum State
		{
			SENDING_HEADER = 0,
			SENDING_BODY = 1,
			SENT = 2,
		};
		HttpResponse();
		HttpResponse(const HttpResponse& obj);
		virtual ~HttpResponse();
		HttpResponse&		operator=(const HttpResponse& obj);
		bool				isHeadersEnc() const;
		const std::string&	getRawHeaders() const;	
		void				encodeHeaders();
		void 				addChunk(std::vector<char>& buf, size_t n);
		void				sendHeaders();
	private:
		std::string		_rawHeaders;
		bool			_isHeadersEnc;
		size_t			_dataSent;
		Encoding 		_enc;
		
		
};

# endif