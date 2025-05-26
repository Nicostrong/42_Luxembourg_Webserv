/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/26 09:55:08 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIB_HPP
# define LIB_HPP

# include <ctime>
# include <poll.h>
# include <string>
# include <netdb.h>
# include <fstream>
# include <sstream>
# include <ostream>
# include <cstdlib>
# include <csignal>
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
# include <queue>
# include <vector>

# define SERVER_VER "WebServ/1.0"
# define CGI_REVISION "CGI/1.1"
# define SERVER_IP "127.0.0.1"
# define CRLF "\r\n"
# define BUFFER_SIZE 1024
# define SEND_BUFFER_SIZE 262144
# define RESPONSE_BUFFER_SIZE 32768
# define MAX_READ_SIZE 32768

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