/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 22:57:51 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST
# define HTTP_REQUEST
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <cstring>
#include <sstream>

# define BUFFER_SIZE 1024

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
		void readReceived(int clientSocket, int serverSocket);
		bool isBadRequest() const;
	private:
		void parseRaw();
		void parseStartLine(std::string &line);
		bool _isValid;
		bool _rawInit;
		std::string _raw;
		size_t _receivedCount;
		size_t _lineParsed;
		HttpMethod _method;
		std::list<std::map<std::string, std::string>> _headers;
		bool _isBadRequest;
};

#endif