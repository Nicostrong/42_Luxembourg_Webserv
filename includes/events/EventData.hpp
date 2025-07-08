/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:27:55 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_DATA_HPP
# define EVENT_DATA_HPP

# include "./IEventHandler.hpp"
# include "./EventMonitoring.hpp"

class	EventData
{
	public:

		EventData(int fd, IEventHandler& ctx, EventMonitoring& em);
		EventData(const EventData &obj);
		~EventData();
		EventData& 				operator=(const EventData& obj);

		int 					getFd() const;
		const IEventHandler&	getCtx() const;
		bool					getCanceled() const;
		void					setCanceled();

		//Events
		void					onRead() const;
		void					onWrite() const;
		void					onClose() const;
		void					onTick() const;

	private:

		const int 				_fd;
		IEventHandler* 			_ctx;
		EventMonitoring*		_em;
		bool					_canceled;
		
};

#endif