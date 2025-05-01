/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/01 13:46:50 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE
# define HTTP_RESPONSE

#include "HttpBase.hpp"
#include "HttpRequest.hpp"

class HttpResponse: public HttpBase
{
	public:
		HttpResponse();
		HttpResponse(const HttpResponse &obj);
		virtual ~HttpResponse();
		HttpResponse &operator=(const HttpResponse &obj);
		bool isEncoded();
		void encodeResponse(const HttpRequest &req);
	private:
		bool	_isEncoded;
		bool	_isComplete;
};

# endif