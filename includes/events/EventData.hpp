/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/06/10 21:52:46 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_DATA_HPP
# define EVENT_DATA_HPP

#include "./IEventHandler.hpp"
#include "./EventMonitoring.hpp"

class EventData
{
	public:
		enum ListenerType
		{
			SERVER = 0,
			CLIENT = 1,	
		};

		EventData(int fd, int type, IEventHandler& ctx, EventMonitoring& em);
		EventData(const EventData &obj);
		~EventData();
		EventData& 				operator=(const EventData& obj);

		int 					getFd() const;
		int						getType() const;
		const IEventHandler&	getCtx() const;
		bool					getCanceled() const;
		void					setCanceled();

		//Events
		void					onRead() const;
		void					onWrite() const;
		void					onClose() const;

	private:
		const int 				_fd;
		const int				_type;
		IEventHandler& 			_ctx;
		EventMonitoring&		_em;
		bool					_canceled;
};

#endif