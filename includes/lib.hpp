/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42luxembourg.lu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:21:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/16 15:15:19 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# include <ctime>
# include <poll.h>
# include <netdb.h>
# include <fstream>
# include <sstream>
# include <ostream>
# include <cstdlib>
# include <fcntl.h>
# include <cstring>
# include <utility>
# include <dirent.h>
# include <iostream>
# include <unistd.h>
# include <algorithm>
# include <exception>
# include <sys/stat.h>
# include <sys/epoll.h>
# include <netinet/in.h>
# include <sys/socket.h>

#include <unistd.h>
#include <iostream>
#include <iomanip>

# include <map>
# include <set>
# include <list>
# include <vector>
# include <queue>

# define SERVER_SOFT "WebServ/1.0"
# define CGI_REVISION "CGI/1.1"
# define SERVER_IP "127.0.0.1"
# define CRLF "\r\n"

# define RESET		"\033[0m"
# define BLACK		"\033[90m"
# define RED		"\033[91m"		//	error log
# define GREEN		"\033[92m"		//	Server log
# define YELLOW		"\033[93m"		//	Location log
# define BLUE		"\033[94m"		//	Directive log
# define MAGENTA	"\033[95m"		//	Method log
# define CYAN		"\033[96m"		//	Debug log

#define PRINT_INFOS() __FILE_NAME__ << ":" << __LINE__ << " at " << __func__ << "()"

# if DEBUG
#  define LOG_DEB(msg)	std::cout << CYAN << "[DEBUG] " << msg << " " << PRINT_INFOS() << RESET << std::endl
# else
#  define LOG_DEB(msg)
# endif

# define LOG_ERROR(msg)	std::cerr << RED << "[ERROR] " << msg << " in " << PRINT_INFOS() << RESET << std::endl

#endif