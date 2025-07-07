# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    excuse.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 14:29:16 by gzenner          ###   ########.fr        #
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
friend = (data.get('friend', ''))
task = (data.get('task', ''))
animal = (data.get('animal', ''))
bad_action = (data.get('bad_action', ''))

print(f"I am deeply sorry {friend}.\nI really wanted to {task} but my {animal} has {bad_action}")