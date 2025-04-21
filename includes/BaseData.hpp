/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:17:51 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 17:30:12 by fdehan           ###   ########.fr       */
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
		
		BaseData(BaseDataType type);
		BaseData(const BaseData &obj);
		virtual ~BaseData();
		BaseData &operator=(const BaseData &obj);
		BaseDataType getType() const;
		static BaseData *getHerited(BaseDataType type);
	protected:
		const BaseDataType _type;
		
};

#endif