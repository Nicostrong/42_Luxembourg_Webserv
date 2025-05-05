/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:21:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/05 09:56:22 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# include <fstream>
# include <sstream>
# include <ostream>
# include <cstdlib>
# include <fcntl.h>
# include <cstring>
# include <iostream>
# include <unistd.h>
# include <algorithm>
# include <exception>
# include <sys/socket.h>
# include <netinet/in.h>

# include <map>
# include <set>
# include <list>
# include <vector>

# define RESET		"\033[0m"
# define BLACK		"\033[90m"
# define RED		"\033[91m"		//	error log
# define GREEN		"\033[92m"		//	Server log
# define YELLOW		"\033[93m"		//	Location log
# define BLUE		"\033[94m"		//	Directive log
# define MAGENTA	"\033[95m"		//	Method log
# define CYAN		"\033[96m"		//	Debug log

# if DEBUG
#  define LOG_DEB(msg)	std::cout << CYAN << "[DEBUG] " << msg << RESET << std::endl
# else
#  define LOG_DEB(msg)
# endif

# define LOG_ERROR(msg)	std::cerr << RED << "[ERROR] " << msg << RESET << std::endl

#endif