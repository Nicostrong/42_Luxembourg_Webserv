/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/19 10:36:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE
# define HTTP_RESPONSE

#include "./lib.hpp"
#include "./HttpBase.hpp"
#include "./HttpParser.hpp"
#include "./HttpRequest.hpp"
#include "./core/chunking/Encoding.hpp"

class Socket;

class HttpResponse: public HttpParser
{
	public:
		enum State
		{
			SNEDING_HEAD = 0,
			SENDING_BODY = 1,
			SENT = 2,
		};
		HttpResponse();
		HttpResponse(const HttpResponse& obj);
		virtual ~HttpResponse();
		HttpResponse&		operator=(const HttpResponse& obj);
		void				sendHead(Socket& ctx) const;	
		void				sendData(Socket& ctx, const std::vector<char>& buff,
			size_t n) const;
		void				sendData(Socket& ctx, const std::string& buff) 
			const;
		void				flushData(Socket& ctx) const;
	private:
		Encoding 		_enc;
		
		
};

# endif