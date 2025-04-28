/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:41:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 20:31:10 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEVENT_HANDLER_CPP
# define IEVENT_HANDLER_CPP

class IEventHandler
{
	public:
		virtual 	 ~IEventHandler() {};
		virtual void onReadEvent(int fd, int type) = 0;
		virtual void onWriteEvent(int fd, int type) = 0;
		virtual void onCloseEvent(int fd, int type) = 0;
	private:
};

#endif