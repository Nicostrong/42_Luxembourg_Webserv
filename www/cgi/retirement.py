# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    retirement.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 13:17:26 by gzenner           #+#    #+#              #
#    Updated: 2025/07/04 10:35:06 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


import sys
import os
import json

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

""" user enters his birthday like 13.12.1988 and the program calculates the days left to retirement (1rst day of 65 years old)
"""

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length)
data = json.loads(line)
birthday = (data.get('birthday', 0)).split('.')

day = int(birthday[0])
month = int(birthday[1])
year = int(birthday[2])

days_left = (40 - (2025 - year - 20))*365

if days_left > 0:
    print(f"You got {days_left} days ({days_left / 365} years) left to work before retirement.:(")
elif days_left == 0:
    print(f"You retire today!!! SUCCESS")
else:
    print(f"You have retired {-days_left} ({days_left / 365} years) days ago!!!")
