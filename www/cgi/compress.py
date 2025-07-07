# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compress.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 13:35:15 by gzenner          ###   ########.fr        #
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

def rle_encode(data: str) -> str:
    if not data:                       # "aaaab" -> "4a1b"
        return ''
    enc, prev, count = [], data[0], 1
    for ch in data[1:]:
        if ch == prev:
            count += 1
        else:
            enc.append(f'{count}{prev}')
            prev, count = ch, 1
    enc.append(f'{count}{prev}')
    return ''.join(enc)

print(rle_encode(text))