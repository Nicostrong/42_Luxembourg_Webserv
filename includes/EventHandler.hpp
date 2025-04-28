/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/28 14:51:45 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_HPP
# define EVENT_HANDLER_HPP

template <typename T>
class EventHandler
{
	public:
		enum BaseDataType
		{
			SERVER = 0,
			CLIENT = 1,
			FILE = 2,
		};

		template <typename T>
		struct EventsHooks
		{
			T* context; 
			void(T::*onRead)(int);
			void(T::*onWrite)(int);
			void(T::*onClose)(int);
		};
		
		EventHandler(int fd, EventsHooks<T> &hooks);
		EventHandler(const EventHandler &obj);
		
		virtual 			~EventHandler();
		EventHandler 		&operator=(const EventHandler &obj);

		int 				getFd() const;
		BaseDataType 		getType() const;

		//Events
		void				onRead() const;
		void				onWrite() const;
		void				onClose() const;

		/*static EventHandler *getHerited(int fd, 
			EventsHooks &hooks);*/
	protected:
		const int _fd;
		EventsHooks<T> &_hooks;
};

#endif