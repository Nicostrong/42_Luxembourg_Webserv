# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rps.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 14:44:21 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/07 11:05:39 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import os
import json
import random

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

options = ["rock", "paper", "scissors"]

content_length = int(os.environ.get('CONTENT_LENGTH', 0))
line = sys.stdin.read(content_length)
data = json.loads(line)
userinput = data.get('userinput', '')
computerinput = options[random.randint(0, 2)]

"""
0 - rock
1 - paper
2 - scissors
"""

if userinput != "rock" and userinput != "paper" and userinput != "scissors":
    print("Bad Input")
    exit()

if computerinput == "rock":
    if userinput == computerinput:
        print("Draw")
    elif userinput == "paper":
        print("Player Wins")
    elif userinput == "scissors":
        print("Computer Wins")

elif computerinput == "paper":
    if userinput == computerinput:
        print("Draw")
    elif userinput == "scissors":
        print("Player Wins")
    elif userinput == "rock":
        print("Computer Wins")

elif computerinput == "scissors":
    if userinput == computerinput:
        print("Draw")
    elif userinput == "rock":
        print("Player Wins")
    elif userinput == "paper":
        print("Computer Wins")