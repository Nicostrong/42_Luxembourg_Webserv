# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calculator.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 10:36:11 by gzenner          ###   ########.fr        #
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
num1 = float(data.get('num1', 0))
num2 = float(data.get('num2', 0))
operator = data.get('operator', '')

if operator == '+':
    result = num1 + num2
elif operator == '-':
    result = num1 - num2
elif operator == '*':
    result = num1 * num2
elif operator == "**":
    result = num1 ** num2
elif operator == '/' and num2 != 0:
    result = num1 / num2
else:
    result = "Input Error"

print(f"{num1} {operator} {num2} = {result}")