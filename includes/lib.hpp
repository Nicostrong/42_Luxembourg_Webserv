/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:12:00 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/30 09:45:21 by fdehan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIB_HPP
# define LIB_HPP

# include <ctime>
# include <cstdio>
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
# include <sys/wait.h>
# include <sys/epoll.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>

# include <unistd.h>
# include <iostream>
# include <iomanip>

# include <map>
# include <set>
# include <list>
# include <queue>
# include <vector>

# define SERVER_VER						"WebServ/1.0"
# define CGI_REVISION					"CGI/1.1"
# define SERVER_IP						"127.0.0.1"
# define CRLF							"\r\n"
# define BUFFER_SIZE					1024
# define SEND_BUFFER_SIZE				262144
# define RESPONSE_BUFFER_SIZE			32768
# define MAX_READ_SIZE					32768
# define BODY_BUFFER_SIZE				32768
# define MAX_CLIENT						1024
# define HEAD_BSIZE						8192
# define EPOLLTICK						1u << 27
# define IDLE_TIMEOUT					75
# define CLIENT_RECEIVING_HEAD_TIMEOUT	60
# define CLIENT_RECEIVING_BODY_TIMEOUT	60
# define CLIENT_SENDING_TIMEOUT			60
# define CGI_SENDING_TIMEOUT 			60
# define CGI_RECEIVING_TIMEOUT			60

# define RESET							"\033[0m"
# define BLACK							"\033[90m"
# define RED							"\033[91m"		//	error log
# define GREEN							"\033[92m"		//	Server log
# define YELLOW							"\033[93m"		//	Location log
# define BLUE							"\033[94m"		//	Directive log
# define MAGENTA						"\033[95m"		//	Method log
# define CYAN							"\033[96m"		//	Debug log

struct t_string 
{
	size_t pos;
	size_t len;
};

#define PRINT_INFOS() __FILE_NAME__ << ":" << __LINE__ << " at " << __func__ << "()"

# if DEBUG
#  define LOG_DEB(msg)	std::cout << CYAN << "[" << getCurrentTimeStr()  << "] [DEBUG] " << msg << " " << PRINT_INFOS() << RESET << std::endl
# else
#  define LOG_DEB(msg)
# endif

# define LOG_ERROR(msg)	std::cerr << RED << "[" << getCurrentTimeStr()  << "] [ERROR] " << msg << " in " << PRINT_INFOS() << RESET << std::endl

inline std::string getCurrentTimeStr() {
	char buffer[9];
	time_t t = std::time(NULL);
	struct tm* tm_info = std::localtime(&t);
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
	return std::string(buffer);
}

#endif