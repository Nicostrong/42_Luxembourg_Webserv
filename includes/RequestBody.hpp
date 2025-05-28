/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/28 10:55:24 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBODY_HPP
# define REQUESTBODY_HPP

#include "Buffer.hpp"
#include "lib.hpp"

#define RAM_BUFF 20480
#define TMP_PATH "/tmp/"

class RequestBody
{
	public:
		RequestBody();
		~RequestBody();
		void			add(Buffer& buff);
	private:
		RequestBody(const RequestBody& obj);
		RequestBody& operator=(const RequestBody& obj);
		void			openTmpFile();
		
		Buffer	 		_buff;
		std::fstream	_fBuff;
		size_t			_size;
		std::string		_fName;
};

#endif