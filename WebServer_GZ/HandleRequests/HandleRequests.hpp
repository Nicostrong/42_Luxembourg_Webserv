/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequests.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:16:01 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/24 16:58:11 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUESTS_HPP
#define HANDLEREQUESTS_HPP

#include "../../includes/HttpRequest.hpp"

class HttpRequest;

class HandleRequests: public HttpRequest
{
/*std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;*/
	
	private:
		bool checkMethod();
		bool checkUri();
		bool checkHttpVersion();
		bool checkBody();
		static void concatResult();
	public:
		void ExecuteRequest();
};

#endif