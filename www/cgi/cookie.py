# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cookie.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/01 13:56:17 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os

cookies = os.environ.get('HTTP_COOKIE', '')

print("Status: 301", end='\r\n')
print("Location: /", end='\r\n')
print("Content-Type: text/html; charset=utf-8", end='\r\n')
print("Set-Cookie: site=http://localhost:8080/; expires=Wed, 2 Jul 20025 8:00:00 GMT,", end='\r\n')
print("Set-Cookie: pseudo=Nicostrong; Path=/; max-age=600\r\n", end='\r\n')
print()
print("<html><body>")
print(f"Vos cookies envoyés : {cookies}")
print("</body></html>")