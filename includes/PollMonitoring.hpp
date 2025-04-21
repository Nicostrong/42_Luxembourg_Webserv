/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollMonitoring.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:31 by fdehan            #+#    #+#             */
/*   Updated: 2025/04/21 18:16:22 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLMONITORING_HPP
# define POLLMONITORING_HPP

#include "BaseData.hpp"
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <poll.h>

#define MAX_CONNECTIONS 20
#define TIMEOUT_POLL 5000

class PollMonitoring
{
	public:
		class PollFullException : public std::exception {
			public:
				const char * what ();
		};

		PollMonitoring();
		PollMonitoring(const PollMonitoring &obj);
		~PollMonitoring();
		PollMonitoring &operator=(const PollMonitoring &obj);
		const std::vector<pollfd> &getFds() const;
		std::vector<BaseData*> &getFdsData();
		void monitor(int fd, short int events, BaseData::BaseDataType type);
		void unmonitor(int fd);
		int  updatePoll();
	private:
		std::vector<pollfd> _fds;
		std::vector<BaseData*> _fdsData;
};

#endif