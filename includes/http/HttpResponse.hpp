/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:24:15 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:33:10 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "./../lib.hpp"
# include "./HttpBase.hpp"
# include "./HttpRequest.hpp"
# include "./../utils/Uri.hpp"
# include "./../utils/Buffer.hpp"

class	HttpResponse: public	HttpBase
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
		void				setStatusStr(const std::string& statusStr);
		void				setRespType(ResponseType type);
		ResponseType		getRespType() const;
		void				encodeHead(const std::string data);

	private:
	
		void				streamHeaders(std::stringstream& ss) const;

		ResponseType	_respType;
		Buffer			_headBuffer;
		
		std::string		_statusStr;
		
};

# endif
