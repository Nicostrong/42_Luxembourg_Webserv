/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/25 16:17:01 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_HPP
# define EVENT_HANDLER_HPP

class EventHandler
{
	public:
		enum BaseDataType
		{
			SERVER = 0,
			CLIENT = 1,
			FILE = 2,
		};
		
		EventHandler(int fd, BaseDataType type, void(*read)(int), 
			void(*write)(int), void(*close)(int));
		EventHandler(const EventHandler &obj);
		virtual ~EventHandler();
		EventHandler &operator=(const EventHandler &obj);
		int getFd() const;
		BaseDataType getType() const;
		static EventHandler *getHerited(int fd, BaseDataType type);
	protected:
		const int _fd;
		const BaseDataType _type;
};

#endif