# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colorize.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/09 09:33:08 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import os
import json

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length)
data = json.loads(line)
r = int(data.get('r', 0))
g = int(data.get('g', 0))
b = int(data.get('b', 0))

print(f"\033[38;2;{r};{g};{b}mEnjoy Colorized Output!\033[0m")