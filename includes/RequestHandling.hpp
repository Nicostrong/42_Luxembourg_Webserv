/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandling.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:28:00 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/29 10:54:27 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLING_HPP
# define REQUEST_HANDLING_HPP

# include "./lib.hpp"
# include "./Uri.hpp"
# include "./CGI.hpp"
# include "./HttpBase.hpp"
# include "./HttpRequest.hpp"
# include "./HttpResponse.hpp"
# include "./server/Server.hpp"

class RequestHandling: public HttpBase
{
	public:
		RequestHandling(const RequestHandling& obj);
		~RequestHandling();
		RequestHandling& operator=(const RequestHandling& obj);
		static void	handleHeaders(Socket& sock);
	private:
		RequestHandling();
		static bool isCGI(Socket& sock);
		static bool isRedirect(Socket& sock);
		static bool isIndexFile(Socket& sock);
		static bool isDirctoryListing(Socket &sock);
		static bool isStaticFile(Socket& sock);
		static void	handlePost(Socket& sock);
		static void handleBodyLength(Socket& sock);
		static void handleTE(Socket& sock);
		static void handleContentLength(Socket& sock);
};

#endif