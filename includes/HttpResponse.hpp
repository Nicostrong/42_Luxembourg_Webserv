/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 09:16:45 by fdehan           ###   ########.fr       */
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
		~HttpResponse();
		HttpResponse &operator=(const HttpResponse &obj);
		bool isEncoded();
		void encodeResponse(const HttpRequest &req);
	private:
		bool _isEncoded;
};

# endif