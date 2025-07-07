# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    password.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 12:50:33 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import os
import json
import string
from string import ascii_lowercase, ascii_uppercase
import random

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length)
data = json.loads(line)
length = int(data.get('length', 0))

if length < 1:
    print("Bad Input")
    exit()

allchars = ascii_lowercase + ascii_uppercase + "0123456789" + "!@#$%%^&*(),./;'[]"

password = ""
for i in range(length):
    password += allchars[random.randint(0, len(allchars) - 1)]

estimated_time_break = 1.001**length - 1

print(f"Password: {password[:1024]}\nEstimated Time to Break:\n{estimated_time_break} minutes.\n({estimated_time_break / 24 / 60} days)")