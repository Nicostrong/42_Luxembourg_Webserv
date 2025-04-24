/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/24 17:09:49 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASEDATA_HPP
# define BASEDATA_HPP

class BaseData
{
	public:
		enum BaseDataType
		{
			SERVER = 0,
			CLIENT = 1,
			FILE = 2,
		};
		
		BaseData(int fd, BaseDataType type);
		BaseData(const BaseData &obj);
		virtual ~BaseData();
		BaseData &operator=(const BaseData &obj);
		int getFd() const;
		BaseDataType getType() const;
		static BaseData *getHerited(int fd, BaseDataType type);
	protected:
		const int _fd;
		const BaseDataType _type;
};

#endif