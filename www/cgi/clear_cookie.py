# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    clear_cookie.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 15:22:48 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/01 15:24:03 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os

print("Status: 301", end='\r\n')
print("Location: /", end='\r\n')
print("Content-Type: text/html; charset=utf-8", end='\r\n')
print(f"Set-Cookie: site=http://localhost:8080/; max-age=0")
print("Set-Cookie: pseudo=Nicostrong; Path=/; max-age=0\r\n", end='\r\n')
print()