# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cookie.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/24 09:07:06 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os

cookies = os.environ.get('HTTP_COOKIE', '')

print("Set-Cookie: user=test_user; Path=/; HttpOnly")
print("Content-Type: text/html\n")

print("<html><body>")
print(f"Vos cookies envoyés : {cookies}")
print("</body></html>")