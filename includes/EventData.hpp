/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 20:13:37 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_DATA_HPP
# define EVENT_DATA_HPP

#include "IEventHandler.hpp"

class EventData
{
	public:
		enum ListenerType
		{
			SERVER = 0,
			CLIENT = 1,	
		};

		EventData(int fd, int type, IEventHandler& ctx);
		EventData(const EventData &obj);
		~EventData();
		EventData& 				operator=(const EventData& obj);

		int 					getFd() const;
		int						getType() const;
		const IEventHandler&	getCtx() const;

		//Events
		void					onRead() const;
		void					onWrite() const;
		void					onClose() const;

	private:
		const int 				_fd;
		const int				_type;
		IEventHandler& 			_ctx;
};

#endif