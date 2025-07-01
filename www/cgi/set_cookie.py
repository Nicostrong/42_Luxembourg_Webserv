# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    set_cookie.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/01 15:50:40 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
from datetime import datetime, timedelta

expire_date = (datetime.utcnow() + timedelta(days=1)).strftime('%a, %d %b %Y %H:%M:%S GMT')

cookies = os.environ.get('HTTP_COOKIE', '')

print("Status: 302", end='\r\n')
print("Location: /", end='\r\n')
print("Content-Type: text/html; charset=utf-8", end='\r\n')
print(f"Set-Cookie: pseudo=Nicostrong; Path=/; expires={expire_date}\r\n", end='\r\n')
print()