/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:02:41 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/23 22:29:04 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BASE_HPP
# define HTTP_BASE_HPP

#define ALLOWED_URI_SPECIALS "-_.~:@/?&=#%+[]!$()*,;"
#define ALLOWED_HEADER_VAL "_ :;.,\\/\"'?!(){}[]@<>=-+*#$&`|~^%"

#include <iostream>
#include <map>
#include <cstring>

class HttpBase
{
	public:
		HttpBase(const HttpBase &obj);
		virtual ~HttpBase();
		HttpBase &operator=(const HttpBase &obj);
	protected:
		HttpBase();
		static bool canBeValidMethod(std::string &method);
		static bool canBeValidPath(std::string &path);
		static bool canBeValidHttpProtocol(std::string &httpVersion);
		static bool isHeaderNameValid(std::string &name);
		static bool isHeaderValueValid(std::string &value);
		static std::string normalizeHeaderName(std::string &name);
		std::string _raw;
		std::string _method;
		std::string _uri;
		std::string _httpVersion;
		std::string _body;
		std::map<std::string, std::string> _headers;
};

#endif