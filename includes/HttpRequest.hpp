/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 11:39:38 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST
# define HTTP_REQUEST
# define BUFFER_SIZE 4096
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <cstring>

class HttpRequest
{
	public:
		enum HttpMethod
		{
			GET = 0,
			POST = 1,
			DELETE = 2,
			INVALID = 3,
		};

		class SocketReadException : public std::exception {
			public:
				const char * what ();
		};

		class RawUninitializedException : public std::exception {
			public:
				const char * what ();
		};
		
		HttpRequest();
		HttpRequest(const HttpRequest &obj);
		~HttpRequest();
		HttpRequest &operator=(const HttpRequest &obj);
		static HttpRequest *decode(int clientSocket, int serverSocket);
	private:
		void readRaw(int clientSocket, int serverSocket);
		void parseRaw();
		bool _isValid;
		bool _rawInit;
		std::string _raw;
		HttpMethod _method;
		std::list<std::map<std::string, std::string>> _headers;
};

#endif