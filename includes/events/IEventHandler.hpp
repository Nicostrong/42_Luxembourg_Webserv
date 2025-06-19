/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:41:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/19 14:46:03 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEVENT_HANDLER_CPP
# define IEVENT_HANDLER_CPP

class EventMonitoring;

class IEventHandler
{
	public:
		virtual 	 ~IEventHandler() {};
		virtual void onReadEvent(int fd, EventMonitoring& em) = 0;
		virtual void onWriteEvent(int fd, EventMonitoring& em) = 0;
		virtual void onCloseEvent(int fd, EventMonitoring& em) = 0;
		virtual void onTickEvent(int fd, EventMonitoring& em) = 0;
	private:
};

#endif