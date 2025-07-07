# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    convert.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 17:27:18 by gzenner          ###   ########.fr        #
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
num = int(data.get('number', 0))
target_base = int(data.get('target_base', 0))

if target_base == 2:
    target_num = bin(num)
elif target_base == 8:
    target_num = oct(num)
elif target_base == 16:
    target_num = hex(num)
else:
    print("Bad Input")
    exit()

print(f"Converting {num} from base 10 to {target_base}: {target_num}")