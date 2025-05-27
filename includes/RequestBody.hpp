/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBody.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:21 by fdehan            #+#    #+#             */
/*   Updated: 2025/05/27 18:28:13 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBODY_HPP
# define REQUESTBODY_HPP

#include "Buffer.hpp"
#include "lib.hpp"

#define RAM_BUFF 20480

class RequestBody
{
	public:
		RequestBody();
		
		~RequestBody();
		
	private:
		RequestBody(const RequestBody& obj);
		RequestBody& operator=(const RequestBody& obj);
		
		Buffer	 		_buff;
		std::fstream	_fBuff;

};

#endif