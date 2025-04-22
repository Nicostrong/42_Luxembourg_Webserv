/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:25:07 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/22 09:58:51 by fdehan           ###   ########.fr       */
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
# define ALLOWED_URI_SPECIALS "-_.~:@/?&=#%+[]!$()*,;"

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
		static bool canBeValidMethod(std::string &method);
		static bool canBeValidPath(std::string &path);
		static bool canBeValidHttpProtocol(std::string &httpVersion);
		std::string _raw;
		size_t _receivedCount;
		size_t _lineParsed;
		std::list<std::map<std::string, std::string>> _headers;
		bool _isBadRequest;
		std::string _method;
		std::string _uri;
		std::string _httpVersion;
};

#endif