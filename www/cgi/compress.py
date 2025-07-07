# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compress.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 14:04:18 by gzenner          ###   ########.fr        #
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
text = (data.get('text', ''))

def compress(data:str) -> str:
    count = 0
    compressed_text = text[0]
    currentchar = text[0]
    for i, c in enumerate(text):
        if c == currentchar:
            count += 1
        else:
            compressed_text += str(count)
            count = 0
            currentchar = c
            compressed_text += currentchar
            count += 1
    compressed_text += str(count)
    return (compressed_text)

print(compress(text))