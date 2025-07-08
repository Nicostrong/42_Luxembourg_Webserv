/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:41:03 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:29:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef IEVENTHANDLER_HPP
# define IEVENTHANDLER_HPP

class	EventMonitoring;

class	IEventHandler
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