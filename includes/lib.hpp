/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:21:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/17 09:45:36 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <ostream>
# include <iostream>
# include <exception>

# include <map>
# include <set>
# include <list>
# include <vector>

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"

# if DEBUG
#  define LOG_DEB(msg)	std::cout << YELLOW << "[DEBUG] " << msg << RESET << std::endl
# else
#  define LOG_DEB(msg)
# endif

# define LOG_ERROR(msg)	std::cerr << RED << "[ERROR] " << msg << RESET << std::endl

#endif