# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    login.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:20 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/24 09:07:45 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
import cgi

form = cgi.FieldStorage()
login = form.getvalue("login", "")

if login:
    print(f"Set-Cookie: login={login}; Path=/")
print("Content-Type: text/html\n")
print("<html><body>")
if login:
    print(f"Hello {login}, you're now connected !")
else:
    print("Please enter your login.")
print("</body></html>")