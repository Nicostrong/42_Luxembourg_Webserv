# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    caesar.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 12:27:20 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import os
import json
import random

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length)
data = json.loads(line)
text = (data.get('text', ''))
shift = int(data.get('shift', 0))
shift %= 126

encrypted_text = ""
for c in text:
    newvalue = ord(c) + shift
    newvalue %= (126-32)
    newvalue += 32
    encrypted_text += chr(newvalue)

print(f"Original Text{text}")
print(f"Encryped Text{encrypted_text}")